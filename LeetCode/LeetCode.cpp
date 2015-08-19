// LeetCode.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "Solution.h"
using namespace std;

int main(void) {
	Solution so;
    vector<int> vec;
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
            vec.push_back(tmp);
        }
        cout << so.largestNumber(vec);
    }
    system("pause");
	return 0;
}
