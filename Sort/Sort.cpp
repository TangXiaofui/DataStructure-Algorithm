#include "Sort.h"
#include <random>
#include <ctime>
#include <functional>
#include <queue>
#include <map>
#include <complex>


Sort::Sort()
{
}


Sort::~Sort()
{
}

//
void Sort::insert(vector<int> &nums)
{
	for (int i = 1; i < nums.size(); i++)
	{
		int tmp = nums[i];
		int j = i;
		while (j > 0 && tmp < nums[j - 1])
		{
			nums[j] = nums[j - 1];
			j--;
		}
		nums[j] = tmp;
	}
}

void Sort::Shell(vector<int> &nums)
{
	for (int span = 10; span > 0; span /= 2)
	{
		for (int i = span; i < nums.size(); i += span)
		{
			int tmp = nums[i];
			int j = i;
			while (j > 0 && tmp < nums[j - span])
			{
				nums[j] = nums[j - span];
				j -= span;
			}
			nums[j] = tmp;
		}
	}
}
void Sort::select(vector<int> &nums)
{
	for (int i = 0; i < nums.size(); i++)
	{
		int k = i;
		for (int j = i + 1; j < nums.size(); j++)
		{
			if (nums[k] > nums[j])
			{
				k = j;
			}
		}
		if (k != i)
		{
			swap(nums[i], nums[k]);
		}
	}
}

void Sort::bubble(vector<int> &nums)
{
	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = 1; j < nums.size() - i; j++)
		{
			if (nums[j] < nums[j - 1])
			{
				swap(nums[j], nums[j - 1]);
			}
		}
	}
}


void merge(vector<int> &nums, int start, int mid, int end, vector<int> &tmp)
{
	int i = start;
	int j = mid + 1;
	int index = start;
	while (i <= mid && j <= end)
	{
		if (nums[i] <= nums[j])
		{
			tmp[index++] = nums[i++];
		}
		else
		{
			tmp[index++] = nums[j++];
		}
	}
	while (i <= mid)
	{
		tmp[index++] = nums[i++];
	}
	while (j <= end)
	{
		tmp[index++] = nums[j++];
	}
	for (int k = start; k <= end; k++)
	{
		nums[k] = tmp[k];
	}

}


void mergeSort(vector<int> &nums, int start, int end, vector<int> &tmp)
{
	if (start < end)
	{
		int mid = start + (end - start) / 2;
		mergeSort(nums, start, mid, tmp);
		mergeSort(nums, mid + 1, end, tmp);
		merge(nums, start, mid, end, tmp);

	}
}


void Sort::merge(vector<int> &nums)
{
	vector<int> tmp(nums.size());
	mergeSort(nums, 0, nums.size() - 1, tmp);
}


int partion(vector<int> &nums, int start, int end)
{
	default_random_engine e(time(nullptr));
	uniform_int_distribution<int> b(0, end - start);
	auto r = bind(b, e);
	int pos = start + r();
	swap(nums[pos], nums[end]);
	int i = start - 1;
	int j = start;
	while (j < end)
	{
		if (nums[j] < nums[end])
		{
			++i;
			if (i != j)
			{
				swap(nums[i], nums[j]);
			}
		}
		j++;
	}
	i++;
	swap(nums[i], nums[end]);
	return i;
}

void quickSort(vector<int> &nums, int start, int end)
{
	if (start < end)
	{
		int pos = partion(nums, start, end);
		quickSort(nums, start, pos - 1);
		quickSort(nums, pos + 1, end);
	}
}

void Sort::quick(vector<int> &nums)
{
	quickSort(nums, 0, nums.size() - 1);
}


void HeapAdjust(vector<int>& nums, int start, int end)
{
	int tmp = nums[start];
	int i = 2 * start + 1;
	while (i < end)
	{
		if (i + 1 < end && nums[i + 1] > nums[i])
			i++;
		if (nums[i] < tmp)
			break;
		nums[start] = nums[i];
		start = i;
		i = 2 * i + 1;
	}
	nums[start] = tmp;
}

void Sort::heap(vector<int> &nums)
{
	int end = nums.size();
	for (int i = end / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(nums, i, end);
	}
	for (int i = end - 1; i >= 0; i--)
	{
		swap(nums[0], nums[i]);
		HeapAdjust(nums, 0, i);
	}
}

void Sort::count(vector<int> &nums)
{
	map<int, int> m;
	for (auto num : nums)
	{
		m[num]++;
	}
	int i = 0;
	for (auto iter = m.begin(); iter != m.end(); iter++)
	{
		while (iter->second)
		{
			nums[i++] = iter->first;
			iter->second--;
		}
	}
}


void Sort::minHeap(vector<int> &num)
{

	priority_queue<int, vector<int>, greater<int>> heap;

	for (int i = 0; i < num.size(); i++)
	{
		if (heap.size() <= 10)
			heap.push(num[i]);
		else
		{
			if (num[i] > heap.top())
			{
				heap.pop();
				heap.push(num[i]);
			}
		}
	}

}