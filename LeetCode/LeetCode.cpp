// LeetCode.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "Solution.h"
using namespace std;
<<<<<<< HEAD
int main(void) {
	int n;
    Solution so;
    vector<int> nums1, nums2;
    nums1 = { 1, 3, 4, 6 };
    nums2 = { 2, 5 };
    cout << so.findMedianSortedArrays(nums1, nums2) << endl;
    nums1 = { 1, 3, 5, 7, 9 };
    nums2 = { 2, 4, 6, 8, 10 };
    cout << so.findMedianSortedArrays(nums1, nums2) << endl;
=======

void print(vector<Interval> &intervals) {
	bool bFlag = false;
	cout << "[";
	for (auto &it : intervals) {
		if (bFlag) {
			cout << ",";
		} else {
			bFlag = true;
		}
		cout << "[" << it.start << "," << it.end << "]";
	}
	cout << "]" << endl;
}
int main(void) {
	//int *fuck = new int[0x60000000 / 4]();
/*
	int size = 0;
	while (1) {
		try {
			new char[1 << 30];
			++size;
		} catch (exception e) {
			cout << e.what() << endl;
			cout << size << endl;
			break;
		}
	}
*/
	Solution so;
	int n;
	while (cin >> n) {
		cout << so.numberToWords(n) << endl;
	}


>>>>>>> b0e4822e7a1b61b44b4bd2bc6414843178ce3850
    system("pause");
	return 0;
}
