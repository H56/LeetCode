#include "Trie.h"


Trie::Trie() {
	root = new TrieNode();
}


Trie::~Trie() {
}

void Trie::insert(string &s, TrieNode *root, int index) {
	if (index < s.length()) {
		map<char, TrieNode *>::iterator it = (root->mapNodes).find((const char)s[index]);
		if (it != root->mapNodes.end()) {
			if (index == s.length() - 1) {
				(it->second)->bEnd = true;
			}
			insert(s, it->second, index + 1);
		} else {
			TrieNode* tmp = new TrieNode;
			//tmp->ch = s[index];
			tmp->bEnd = index == s.length() - 1;
			(root->mapNodes)[s[index]] = tmp;
			insert(s, tmp, index + 1);
		}
	}
}
bool Trie::search(string &key, TrieNode* root, int index) {
	if (index < key.length()) {
		auto it = root->mapNodes.find(key[index]);
		if (it == root->mapNodes.end()) {
			return false;
		} else {
			return search(key, it->second, index + 1);
		}
	}
	return root->bEnd;
}
bool Trie::startsWith(string &prefix, TrieNode* root, int index) {
	if (index < prefix.length()) {
		auto it = root->mapNodes.find(prefix[index]);
		if (it == root->mapNodes.end()) {
			return false;
		} else {
			return startsWith(prefix, it->second, index + 1);
		}
	}
	return true;
}
