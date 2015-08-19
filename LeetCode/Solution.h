#pragma once
#include "Structs.h"
#include "Trie.h"

#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <unordered_map>
#include <time.h>
#include <string>
#include <unordered_set>
#include <fstream>
#include <stack>
#include <queue>
#include <sstream>
#include <iostream>
#include <sstream>
using namespace std;

class Solution {
private:
    stringstream ss;
	vector<vector<int>> vec2;
	unordered_set<UndirectedGraphNode *> old;
	bool bFlag;
	const int UNREAD = INT_MAX;
public:
	Solution();
	~Solution();
	bool isNumber(string s);
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict);
	void removeFromDict(unordered_set<string> &source, unordered_set<string> &dict);
	vector<string> findSimilarity(string word, unordered_set<string> &dict);
	string fractionToDecimal(int numerator, int denominator);
	int maxPoints(vector<Point> &points);
	int countMax(float *pArray, int length);
	void quickSort(float *pArray, int start, int end);
	vector<vector<int> > threeSum(vector<int> &num);
private:
	void quickSort(int *num, int len);
	int binarySearch(vector<int> &num, int data, int start);
public:
	int findMin(vector<int> &num);
	int uniquePaths(int m, int n);
	int uniquePaths1(int m, int n);
	vector<int> grayCode(int n);
	void sortColors(int A[], int n);
	int findPeakElement(const vector<int> &num);
	string addBinary(string a, string b);
	unsigned int reverseBits(unsigned int n);
	int compareVersion(string version1, string version2);
private:
	int compareInt(const char *str1, int len1, const char *str2, int len2);
public:
	void rotate(int nums[], int n, int k);
	int trailingZeroes(int n);
	string convertToTitle(int n);
	bool isValidSudoku(vector<vector<char> > &board);
private:
	bool wordBreak(string &s, int pos, unordered_set<string> &dict, bool &flag);
public:
	bool wordBreak(string s, unordered_set<string> &dict);
	ListNode *detectCycle(ListNode *head);
	int numDecodings(string s);
private:
	int numDecodings_sustr(string s);
private:
	int isHave(const char *str, int len, char ch);
public:
	int lengthOfLongestSubstring(string s);
	int sqrt(int x);

	ListNode *partition(ListNode *&head, int x);
	ListNode *partition(ListNode *&head, ListNode *&end, int x);
	ListNode *sortList(ListNode *&head, ListNode *&end);
	ListNode *sortList(ListNode *head);
private:
	vector<vector<int>> isPathSum(TreeNode *root, int sum);
public:
	vector<vector<int>> pathSum(TreeNode *root, int sum);

private:
	int minPathSum(vector<vector<int>> &grid, int row, int col);
public:
	int minPathSum(vector<vector<int> > &grid);
	// improved method
	int improve_minPathSum(vector<vector<int> > &grid);
	string simplifyPath(string path);
	string simplifyPath1(string path);
private:
	TreeNode* flatten1(TreeNode *root);
public:
	void flatten(TreeNode *root);
	vector<int> rightSideView(TreeNode *root);
	ListNode* removeElements(ListNode* head, int val);
	bool isHappy(int n);
	vector<vector<int> > zigzagLevelOrder(TreeNode *root);
	ListNode* rotateRight(ListNode* head, int k);
	//string largestNumber(vector<int>& nums);
	ListNode* deleteDuplicates1(ListNode* head);
	ListNode* deleteDuplicates(ListNode* head);
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost);
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node);
private:
	bool isPalindrome(string &str, int start, int end);
	void partition(string &s, int index, vector<string> &cur, vector<vector<string>> &vec2Ret);
public:
	vector<vector<string>> partition(string s);
private:
	void quickSort_three(int *num, int len);
	int binarySearch_three(vector<int> &num, int data, int start);
public:
	int threeSumClosest(vector<int>& nums, int target);
	int threeSumClosest1(vector<int>& num, int target);
	int countPrimes(int n);
	void solve(vector<vector<char>> &board);

private:
	void combinationSum(vector<int> &cur, vector<vector<int>> &vec2Res, vector<int> &candidates, vector<int>::iterator index, int target);
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target);
	bool isIsomorphic(string s, string t);
	int rangeBitwiseAnd(int m, int n);
private:
	int minimumTotal(vector<vector<int>> &triangle, int row, int col);
public:
	int minimumTotal(vector<vector<int> > &triangle);
	void reorderList(ListNode* head);
private:
	bool isValidBST(TreeNode* root, int &min, int &max);
public:
	bool isValidBST(TreeNode* root);

	TreeNode* sortedListToBST(ListNode* head);
	ListNode* insertionSortList(ListNode* head);
private:
	ListNode* merge2Lists(ListNode* l1, ListNode* l2);
public:
	ListNode* mergeKLists(vector<ListNode*>& lists);
public:
	void reverseWords(string &s);
public:
	int evalRPN(vector<string>& tokens);
	bool containsNearbyDuplicate(vector<int>& nums, int k);
	int minSubArrayLen(int s, vector<int>& nums);
public:
	int kthSmallest(TreeNode* root, int k);
private:
	bool DFS(map<int, vector<int>>::iterator &itStart, map<int, vector<int>> &map, const int &iLable);
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites);
	int calculate(string s);
private:
	bool lowestCommonAncestor(TreeNode* root, TreeNode* &p, vector<TreeNode*> &vec);
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
	int countNodes(TreeNode* root);

private:
	void letterCombinations(string &digits, int index, vector<string> &vec);

public:
	vector<string> letterCombinations(string digits);
	bool searchMatrix(vector<vector<int>>& matrix, int target);
	int countDigitOne(int n);
	vector<string> generateParenthesis(int n);
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);
	vector<int> productExceptSelf(vector<int>& nums);
	vector<int> majorityElement(vector<int>& nums);
	int ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict);
	int divide(int dividend, int divisor);
	int maximalSquare(vector<vector<char>>& matrix);
	std::string longestPalindrome(std::string s);
private:
     void onceSortBigHeap(vector<int> &vec, int end);
     void binaryTreePaths(vector<string> &vec, TreeNode* &root, vector<int> &vecPath);
public:
     int addDigits(int num);
     vector<string> binaryTreePaths(TreeNode* root);
     string largestNumber(vector<int>& nums);
};

