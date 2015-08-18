#pragma once
#include <iostream>
#include "Solution.h"
class Trie {
public:
	Trie();
	~Trie();
private:
	TrieNode* root;
	void insert(string &s, TrieNode *root, int index);
	bool search(string &key, TrieNode* root, int index);
	bool startsWith(string &prefix, TrieNode* root, int index);
public:
	// Inserts a word into the trie.
	void insert(string s) {
		insert(s, root, 0);
	}

	// Returns if the word is in the trie.
	bool search(string key) {
		return search(key, root, 0);
	}

	// Returns if there is any word in the trie
	// that starts with the given prefix.
	bool startsWith(string prefix) {
		return startsWith(prefix, root, 0);
	}
};