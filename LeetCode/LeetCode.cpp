// LeetCode.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "Solution.h"
using namespace std;

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
	vector<Interval> intervals;
	intervals.push_back(Interval(1, 5));
	vector<Interval> result = so.insert(intervals, Interval(0, 6));
	print(result);

	result = so.insert(intervals, Interval(6, 8));
	print(result);

	result = so.insert(intervals, Interval(2, 3));
	print(result);

	result = so.insert(intervals, Interval(0, 0));
	print(result);

	intervals.push_back(Interval(6, 7));
	result = so.insert(intervals, Interval(5, 6));
	print(result);

	result = so.insert(intervals, Interval(5, 5));
	print(result);


    system("pause");
	return 0;
}
