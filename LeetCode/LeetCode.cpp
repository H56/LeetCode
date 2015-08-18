// LeetCode.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "Solution.h"
using namespace std;

int main(void) {
	Solution so;
    TreeNode *root = new TreeNode(0);
    root->left = new TreeNode(1);
    vector<string> re = so.binaryTreePaths(root);
    for (auto &it : re) {
        cout << it << endl;
    }
    cout << "fuck github" << endl;
    system("pause");
	return 0;
}
