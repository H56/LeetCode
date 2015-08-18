#pragma once
#include <iostream>
#include <string>
using namespace std;
class WordDictionary {
public:
	WordDictionary();
	~WordDictionary();
private:
	struct node {
		node *next[27];
		node() {
			for (int i = 0; i < 27; ++i) {
				next[i] = NULL;
			}
		}
	} data;
	bool search(string &word, node *pData, int iStart);
public:
	// Adds a word into the data structure.
	void addWord(string word);

	// Returns if the word is in the data structure. A word could
	// contain the dot character '.' to represent any one letter.
	bool search(string word) {
		return search(word, &data, 0);
	}
};