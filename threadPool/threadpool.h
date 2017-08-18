#ifndef threadpool_H
#define threadpool_H
#include <thread>
#include <functional>
#include <future>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <memory>
#include <stdexcept>
using namespace std;

class ThreadPool
{
public:
	ThreadPool(int n);
	~ThreadPool();
	template <typename FUNC, typename... ARGS>
	auto enqueue(FUNC &&func, ARGS&&... args)->future<typename std::result_of<FUNC(ARGS...)>::type>;

private:
	bool isStop;
	vector<std::thread> workers;
	queue<function<void()>> taskqueue;
	mutex mtx;
	condition_variable cond;
};


ThreadPool::ThreadPool(int n)
	:isStop(false)
{
	for (int i = 0; i < n; i++)
	{
		workers.emplace_back([this]()
		{
			for (;;)
			{
				function<void()> t;
				{
					unique_lock<mutex> lock(mtx);
					cond.wait(lock, [this]()
					{
						return isStop || !taskqueue.empty();
					});
					if (isStop && taskqueue.empty())
						return;

					t = std::move(taskqueue.front());
					taskqueue.pop();
				}
				t();
			}
		});
	}

}

ThreadPool::~ThreadPool()
{
	{
		unique_lock<mutex> lock;
		isStop = true;
	}
	cond.notify_all();
	//这里必须用引用
	for (auto &t : workers)
	{
		t.join();
	}
}
template <typename FUNC, typename... ARGS>
auto ThreadPool::enqueue(FUNC &&func, ARGS&&... args)->future<typename std::result_of<FUNC(ARGS...)>::type>
{
	using return_type = typename std::result_of<FUNC(ARGS...)>::type;

	auto t = make_shared<std::packaged_task<return_type()>>(
		std::bind(std::forward<FUNC>(func), std::forward<ARGS>(args)...));

	std::future<return_type> res = t->get_future();
	{
		unique_lock<mutex> lock(mtx);
		if (isStop)
			throw std::runtime_error("threads has exist");
		taskqueue.emplace([t]()
		{
			//注意解引用
			(*t)();
		});
	}
	cond.notify_one();
	return res;
}


#endif // threadpool_H

