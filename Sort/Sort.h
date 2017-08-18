#pragma once
#include <vector>
using namespace std;

class Sort
{
public:
	Sort();
	~Sort();

	void insert(vector<int> &nums);
	void Shell(vector<int> &nums);
	void select(vector<int> &nums);
	void bubble(vector<int> &nums);
	void merge(vector<int> &nums);
	void quick(vector<int> &nums);
	void heap(vector<int> &nums);
	void count(vector<int> &nums);

	//构建最小堆
	void minHeap(vector<int> &num);
};

