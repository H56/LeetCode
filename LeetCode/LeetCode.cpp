// LeetCode.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "Solution.h"
using namespace std;
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
    system("pause");
	return 0;
}
