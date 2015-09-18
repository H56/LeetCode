// LeetCode.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "Solution.h"
using namespace std;

int main(void) {
	Solution so;
	int n;
	while (cin >> n) {
		cout << so.numberToWords(n) << endl;
	}

    system("pause");
	return 0;
}
