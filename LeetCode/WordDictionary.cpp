#include "WordDictionary.h"


WordDictionary::WordDictionary() {
}


WordDictionary::~WordDictionary() {
}

bool WordDictionary::search(string &word, node *pData, int iStart) {
	for (int i = iStart; i < word.length(); ++i) {
		if (word[i] == '.') {
			for (int j = 0; j < 26; ++j) {
				if (pData->next[j] != NULL && search(word, pData->next[j], i + 1)) {
					return true;
				}
			}
			return false;
		}
		pData = pData->next[word[i] - 'a'];
		if (pData == NULL) {
			return false;
		}
	}
	if (pData->next[26] != NULL) {
		return true;
	}
	return false;
}

void WordDictionary::addWord(string word) {
	node *pTmp = &data;
	for (int i = 0; i < word.length(); ++i) {
		if (pTmp->next[word[i] - 'a'] == NULL) {
			pTmp->next[word[i] - 'a'] = new node();
		}
		pTmp = pTmp->next[word[i] - 'a'];
	}
	pTmp->next[26] = pTmp;
}