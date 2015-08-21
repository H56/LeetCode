// LeetCode.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "Solution.h"
using namespace std;

int main(void) {
	Solution so;    
    int n, target;
    while (cin >> n >> target) {
        vector<int> vec;
        for (auto i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
            vec.push_back(tmp);
        }
        vec = so.searchRange(vec, target);
        for (auto &it : vec) {
            cout << it << " ";
        }
        cout << endl;
    }
    
    system("pause");
	return 0;
}
