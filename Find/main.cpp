#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
	int findFirst(vector<int> &data, int k) {
		int left = 0;
		int right = data.size() - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (k <= data[mid]) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		return data[right + 1] == k ? right + 1 : -1;
	}

	int findLast(vector<int> &data, int k) {
		int left = 0;
		int right = data.size() - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (k < data[mid]) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		return data[left - 1] == k ? left - 1 : -1;
	}
	int GetNumberOfK(vector<int> data, int k) {
		if (data.size() == 0)
			return 0;
		int pos1 = findFirst(data, k);
		int pos2 = findLast(data, k);
		if (pos1 == -1) {
			return 0;
		}
		else if (pos1 == pos2) {
			return 1;
		}
		else
			return pos2 - pos1 + 1;
	}
};


int main()
{
	//int mid = 1 + (1 - 1) >> 1;
	vector<int> tmp = { 1,2,3,4,5 };
	cout << Solution().GetNumberOfK(tmp, 3);
}