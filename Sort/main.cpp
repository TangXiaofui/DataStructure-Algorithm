#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include "Sort.h"
#include <functional>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;
static int NUM = 500;



void testSort(vector<int> unorder)
{

	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	Sort s;
	s.insert(unorder);
	//s.Shell(unorder);
	//s.select(unorder);
	//s.bubble(unorder);
	//s.merge(unorder);
	//s.quick(unorder);
	//s.heap(unorder);
	//s.count(unorder);
	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

	chrono::duration<double> timeSpan = chrono::duration_cast<chrono::duration <double>>(t2 - t1);

	for (int i = 0; i < unorder.size(); i++)
	{
		cout << setw(5) << unorder[i];
		if (i != 0 && i % 20 == 0)
			cout << endl;
	}
	cout << endl;
	cout << "Time Span : " << timeSpan.count() << "seconds" << endl;
}


int main()
{
	default_random_engine e(time(nullptr));
	uniform_int_distribution<int>  dist(0, NUM);
	auto r = std::bind(dist, e);

	vector<int> unorder;


	for (int i = 0; i < NUM; i++)
	{
		unorder.emplace_back(r());
	}

	testSort(unorder);



}