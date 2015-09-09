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
	int n;
	while (cin >> n) {
		cout << so.numberToWords(n) << endl;
	}


    system("pause");
	return 0;
}
