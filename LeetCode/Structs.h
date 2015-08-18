#pragma once
#include <vector>
#include <map>
using namespace std;
class TrieNode {
public:
	bool bEnd;
	map<char, TrieNode *> mapNodes;
	// Initialize your data structure here.
	TrieNode() {
		//char ch;
		// 		bool bEnd;
		// 		map<char, TrieNode*> mapNodes; 
	}
};
// Definition for undirected graph.
struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};
struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};
};
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
