#include <iostream>
#include <memory>
using namespace std;
template <typename T>
class SharedPtr
{
public:
	explicit SharedPtr(T *ptr) :ptr_(ptr), count_(new unsigned int(1)) {

	}
	~SharedPtr()
	{
		(*count_)--;
		if ((*count_) == 0)
		{
			delete ptr_;
			delete count_;
		}
	}
	SharedPtr(const SharedPtr<T>& rh);
	SharedPtr<T>& operator=(SharedPtr<T> &rh);
	SharedPtr<T>& operator=(SharedPtr<T> &&rh);
	T& operator*() {
		return *ptr_;
	}
	T* operator->() {
		return ptr_;
	}
private:
	T *ptr_;
	unsigned int *count_;
};

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& rh)
	:ptr_(rh.ptr_), count_(rh.count_)
{
	(*count_)++;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T> &rh)
{
	delete ptr_;
	ptr_ = rh.ptr_;
	count_ = rh.count_;
	++*count_;
	return *this;
}
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T> &&rh)
{
	delete ptr_;
	ptr_ = rh.ptr_;
	count_ = rh.count_;
	++*count_;
	return *this;
}
class test
{
public:
	test(int val = 0) :a(val)
	{
		cout << "test constru  " << a << endl;
	}
	~test()
	{
		cout << "test destruc  " << a << endl;
	}
	int a;
};

int main()
{

	SharedPtr<test> p2(new test(10));
	{
		SharedPtr<test> ptr(new test);
		ptr = p2;
	}

	cout << p2->a << endl;
	//shared_ptr<test> ptr(new test);
	//ptr = shared_ptr<test>(new test(10));

}