// LeetCode.cpp : �������̨Ӧ�ó������ڵ㡣
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
