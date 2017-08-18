#include "threadpool.h"
#include <iostream>
#include <stack>
using namespace std;

int main()
{

	ThreadPool t(5);
	vector<future<int>> res;
	for (int i = 0; i < 10; i++)
	{
		res.emplace_back(t.enqueue([](int i)
		{
			cout << i << endl;
			return i;
		},
			i));
	}
	cout << "------------------------" << endl;

}