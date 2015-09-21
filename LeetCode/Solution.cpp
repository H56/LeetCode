#include "Solution.h"

string strArray[10] = { " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };


Solution::Solution() {
}


Solution::~Solution() {
}

std::string Solution::longestPalindrome(std::string s) {
	if (s.length() < 2) {
		return s;
	}
	int len = s.length(), max_start = 0, max_len = 0, start = 0;
	for (int left = start, right = start; start < len && (len - start) > (max_len >> 1); ) {
		right = left = start;
		while (right < len - 1 && s[right + 1] == s[right]) {
			++right;
		}
		start = right + 1;
		for (; left >= 0 && right < len && (s[left] == s[right]); --left, ++right);
		max_len = max_len < (right - left - 1) ? (max_start = left + 1, right - left - 1) : max_len;
	}
	return s.substr(max_start, max_len);
}

bool Solution::isNumber(string s) {
	int i = 0;
	bool bRet = false;
	for (; i < s.length(); ++i) {
		if (s[i] != ' ') {
			break;
		}
	}
	if (s[i] == '-' || s[i] == '+') {
		++i;
	}
	int iValideDot = 0, iValideE = 0;
	for (; i < s.length(); ++i) {
		if (s[i] <= '9' && s[i] >= '0') {
			bRet = true;
			continue;
		} else if (s[i] == ' ') {
			break;
		} else if (s[i] == '.' && iValideDot == 0 && iValideE == 0) {
			iValideDot++;
		} else if (s[i] == 'e' && iValideE == 0 && bRet) {
			iValideE++;
			if (s[++i] <= '9' && s[i] >= '0') {
				continue;
			} else if (s[i] == '-' || s[i] == '+') {
				bRet = false;
				continue;
			} else {
				return false;
			}

		} else {
			return false;
		}
	}
	for (; i < s.length(); ++i) {
		if (s[i] != ' ') {
			return false;
		}
	}
	return bRet;
}

vector<vector<string>> Solution::findLadders(string start, string end, unordered_set<string> &dict) {
	int iLevel = 0;
	vector<vector<string>> vec2Ret;
	map<int, unordered_set<string>> mapLevel;
	unordered_set<string> setTemp;
	setTemp.insert(end);
	mapLevel[0] = setTemp;
	// 		dict.insert(start);
	unordered_set<string> dictTemp = dict;
	bool bStop = false;
	for (iLevel = 0; iLevel < dict.size() && !bStop; ++iLevel) {
		if (mapLevel[iLevel].size() <= 0) {
			return vec2Ret;
		}
		removeFromDict(mapLevel[iLevel], dictTemp);
		setTemp.clear();
		for (unordered_set<string>::iterator iter = mapLevel[iLevel].begin(); iter != mapLevel[iLevel].end(); ++iter) {
			vector<string> vecTemp = findSimilarity(*iter, dictTemp);
			for (vector<string>::iterator iterTemp = vecTemp.begin(); iterTemp != vecTemp.end(); ++iterTemp) {
				mapLevel[iLevel + 1].insert(*iterTemp);
			}
		}
	}
	vector<string> vecString;
	vecString.push_back(start);
	vec2Ret.push_back(vecString);
	for (int i = mapLevel.size() - 1; i >= 0; --i) {
		// 			for(vector<vector<string>>::iterator iter = vec2Ret.begin(); iter != vec2Ret.end(); ++iter) {
		int iSize = vec2Ret.size();
		for (int iVect = 0; iVect < iSize; ++iVect) {
			vector<string> vecTemp = findSimilarity(*(vec2Ret[iVect].end() - 1), mapLevel[i]);
			vector<string> vecOriginal = vec2Ret[iVect];
			for (vector<string>::iterator iterTemp = vecTemp.begin(); iterTemp != vecTemp.end(); ++iterTemp) {
				if (iterTemp == vecTemp.begin()) {
					vec2Ret[iVect].push_back(*iterTemp);
					continue;
				}
				vector<string> vecEle = vecOriginal;
				vecEle.push_back(*iterTemp);
				vec2Ret.push_back(vecEle);
			}
		}
	}
	return vec2Ret;
}

void Solution::removeFromDict(unordered_set<string> &source, unordered_set<string> &dict) {
	if (source.size() <= 0 || dict.size() <= 0) {
		return;
	}
	for (unordered_set<string>::iterator iter = source.begin(); iter != source.end(); ++iter) {
		unordered_set<string>::iterator it = dict.find(*iter);
		if (it != dict.end()) {
			dict.erase(it);
		}
	}
}
vector<string> Solution::findSimilarity(string word, unordered_set<string> &dict) {
	vector<string> vecStrRet;
	for (int i = 0; i < word.length(); ++i) {
		for (int j = 'a'; j <= 'z'; ++j) {
			string strTemp = word;
			strTemp[i] = j;
			if (dict.find(strTemp) != dict.end()) {
				vecStrRet.push_back(strTemp);
			}
		}
	}
	return vecStrRet;
}

string Solution::fractionToDecimal(int numerator, int denominator) {
	string strRet;
	if (denominator == 0) {
		return "";
	}
	if ((denominator < 0 && numerator > 0) || (denominator > 0 && numerator < 0)) {
		strRet += "-";
	}
	unsigned int uiNumerator = abs(numerator);
	unsigned int uiDenominator = abs(denominator);
	strRet += to_string(uiNumerator / uiDenominator);
	long long remainder = uiNumerator % uiDenominator;
	vector<unsigned int> vecRemainders;
	if (remainder == 0) {
		return strRet;
	}
	strRet += ".";
	vecRemainders.push_back(remainder);
	bool bTerminate = false;
	for (int i = strRet.length(); !bTerminate && remainder;) {
		strRet += (char)((remainder * 10 / uiDenominator) + '0');
		int iIndex = 0;
		remainder = remainder * 10 % uiDenominator;
		for (iIndex = 0; iIndex < vecRemainders.size(); ++iIndex) {
			if (vecRemainders[iIndex] == remainder) {
				break;
			}
		}
		if (iIndex < vecRemainders.size()) {
			string strSub = "(" + strRet.substr(iIndex + i) + ")";
			strRet.replace(iIndex + i, strRet.length() - iIndex - i, strSub);
			bTerminate = true;
		}
		vecRemainders.push_back(remainder);
	}
	return strRet;
}

int Solution::maxPoints(vector<Point> &points) {
	if (points.size() <= 0) {
		return 0;
	}
	int maxRet = 0;
	vector<float> veSlope;
	float *pArray = new float[points.size()];
	int iIndex = 0;
	veSlope.resize((points.size() - 1) * (points.size() - 1) + 1);
	for (int i = 0; i < points.size(); ++i) {
		int iAdd = 1;
		for (int j = i + 1; j < points.size(); ++j) {
			float fSlope, fShift_x = (float)(points[i].y - points[j].y), fShift_y = (float)(points[i].x - points[j].x);
			if (abs(fShift_x) >= FLT_EPSILON) {
				fSlope = fShift_y / fShift_x;
			} else if (abs(fShift_y) >= FLT_EPSILON) {
				fSlope = FLT_MAX;
			} else {
				++iAdd;
				fSlope = -FLT_MAX;
			}
			veSlope[iIndex] = fSlope;
			pArray[j] = veSlope[iIndex];
			++iIndex;
		}
		for (int k = 1; k < i + 1; ++k) {
			pArray[k] = veSlope[(2 * points.size() - k) * (k - 1) / 2 + i - k];
		}
		cout << "\n-------------------------------------------------------" << endl;
		for (int i = 1; i < points.size(); ++i) {
			cout << pArray[i] << " ";
		}
		cout << "\n-------------------------------------------------------" << endl;
		int iCount = countMax(pArray + 1, points.size() - 1) + iAdd;
		if (maxRet < iCount) {
			maxRet = iCount;
		}
	}
	delete pArray;
	return maxRet;
}

int Solution::countMax(float *pArray, int length) {
	if (nullptr == pArray || length <= 0) {
		return 0;
	}
	int iCount = 1, iMaxCount = 1;
	quickSort(pArray, 0, length - 1);
	int index = 0;
	for (index = 0; index < length; ++index) {
		cout << pArray[index] << " ";
		if (pArray[index] != -FLT_MAX) {
			break;
		}
	}
	cout << endl;
	if (index >= length) {
		return 0;
	}
	float tmp = pArray[index];
	for (int i = index + 1; i < length; ++i) {
		if (abs(tmp - pArray[i]) < FLT_EPSILON) {
			++iCount;
		} else {
			if (iCount > iMaxCount) {
				iMaxCount = iCount;
			}
			iCount = 1;
			tmp = pArray[i];
		}
	}
	if (iCount > iMaxCount) {
		iMaxCount = iCount;
	}
	return iMaxCount;
}

void Solution::quickSort(float *pArray, int start, int end) {
	if (nullptr == pArray || start >= end) {
		return;
	}
	int iLeft = start, iRight = end;
	float tmp = pArray[iLeft];
	while (iLeft < iRight) {
		while (iLeft < iRight && pArray[iRight] >= tmp) {
			--iRight;
		}
		pArray[iLeft] = pArray[iRight];
		while (iLeft < iRight && pArray[iLeft] <= tmp) {
			++iLeft;
		}
		pArray[iRight] = pArray[iLeft];
	}
	pArray[iLeft] = tmp;
	quickSort(pArray, start, iLeft - 1);
	quickSort(pArray, iLeft + 1, end);
}

vector<vector<int> > Solution::threeSum(vector<int> &num) {
	vector<vector<int>> vec2Ret;
	if (num.size() <= 0) {
		return vec2Ret;
	}
	quickSort(&num[0], num.size());
	int tmp1 = num[0] + 1;
	for (int i = 0; i < num.size(); ++i) {
		if (num[i] == tmp1) {
			continue;
		}
		int tmp2 = num[i + 1] + 1;
		for (int j = i + 1; j < num.size(); ++j) {
			if (num[j] == tmp2) {
				continue;
			}
			int iIndex = binarySearch(num, -(num[i] + num[j]), j + 1);
			if (iIndex > 0) {
				vector<int> vecTemp;
				vecTemp.push_back(num[i]);
				vecTemp.push_back(num[j]);
				vecTemp.push_back(num[iIndex]);
				vec2Ret.push_back(vecTemp);
			}
			tmp2 = num[j];
		}
		tmp1 = num[i];
	}
	return vec2Ret;
}

void Solution::quickSort(int *num, int len) {
	int iStart = 0, iEnd = len - 1;
	int tmp = num[0];
	if (iStart >= iEnd) {
		return;
	}
	while (iStart < iEnd) {
		while (iStart < iEnd && num[iEnd] > tmp) {
			--iEnd;
		}
		num[iStart] = num[iEnd];
		while (iStart < iEnd && num[iStart] <= tmp) {
			++iStart;
		}
		num[iEnd] = num[iStart];
	}
	num[iStart] = tmp;
	quickSort(num, iStart);
	quickSort(num + iStart + 1, len - iStart - 1);
}

int Solution::binarySearch(vector<int> &num, int data, int start) {
	int iStart = start, iEnd = num.size() - 1;
	if (iStart > iEnd) {
		return -1;
	}
	if (iStart == iEnd) {
		return num[iStart] == data ? iStart : -1;
	}
	int iMid;
	while (iStart <= iEnd) {
		iMid = (iStart + iEnd) / 2;
		if (num[iMid] < data) {
			iStart = iMid + 1;
		} else if (num[iMid] > data) {
			iEnd = iMid - 1;
		} else {
			return iMid;
		}
	}
	return -1;
}
int Solution::findMin(vector<int> &num) {
	int iLength = num.size();
	if (iLength <= 0) {
		return -1;
	}
	int *pArray = &num[0], temp = num[0], start = 0, end = num.size() - 1, data = pArray[0];
	if (iLength == 1) {
		return pArray[0];
	}
	if (iLength == 2) {
		return pArray[0] < pArray[1] ? pArray[0] : pArray[1];
	}
	while (1) {
		int iMid = (start + end) / 2;
		if (pArray[iMid] < data) {
			end = iMid - 1;
			if (start >= end) {
				return pArray[end] < data ? pArray[end] : pArray[end + 1];
			}
		} else {
			start = iMid + 1;
			if (start >= end) {
				return pArray[end] < data ? pArray[end] : (end == iLength - 1 ? data : pArray[end + 1]);
			}
		}
	}
}

int Solution::uniquePaths(int m, int n) {
	if (m <= 1) {
		return 1;
	} else if (n <= 1) {
		return 1;
	}
	vector<vector<int>> vec2Path;
	vec2Path.resize(m);
	for (int i = 0; i < m; ++i) {
		vec2Path[i].resize(n, 1);
	}
	for (int i = 1; i < m; ++i) {
		for (int j = 1; j < n; ++j) {
			vec2Path[i][j] = vec2Path[i - 1][j] + vec2Path[i][j - 1];
		}
	}
	return vec2Path[m - 1][n - 1];
}

int Solution::uniquePaths1(int m, int n) {
	if (m <= 1) {
		return 1;
	} else if (n <= 1) {
		return 1;
	}
	return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
}

vector<int> Solution::grayCode(int n) {
	vector<int> vecRet;

	if (n <= 0) {
		return vecRet;
	}
	vecRet.resize(1 << n);
	int *pRet = &vecRet[0];
	pRet[0] = 0; pRet[1] = 1;
	for (int i = 2; i <= n; ++i) {
		int iPreLen = (1 << (i - 1));
		for (int j = iPreLen - 1, k = iPreLen; j >= 0; --j, ++k) {
			pRet[k] = pRet[j] ^ iPreLen;
		}
	}
	return vecRet;
}

void Solution::sortColors(int A[], int n) {
	int iWhiteCount = 0, iBlueCount = 0, iStart = 0;
	for (int i = 0; i < n; ++i) {
		switch (A[i]) {
		case 0: A[iStart++] = 0; break;
		case 1: ++iWhiteCount; break;
		case 2: ++iBlueCount; break;
		default: break;
		}
	}
	for (; iStart < iWhiteCount; ++iStart) {
		A[iStart] = 1;
	}
	for (; iStart < iBlueCount; ++iStart) {
		A[iStart] = 2;
	}
}

int Solution::findPeakElement(const vector<int> &num) {
	bool bFlag = true;
	int iLen = num.size(), iTemp = num[0];
	if (iLen <= 0) {
		return -1;
	}
	if (iLen == 1) {
		return 0;
	}
	if (num[0] > num[1]) {
		return 0;
	}
	if (num[iLen - 1] > num[iLen - 2]) {
		return iLen - 1;
	}
	for (int i = 1; i < iLen - 1; ++i) {
		if (num[i - 1] < num[i]) {
			if (num[i] > num[i + 1]) {
				return i;
			}
		}
	}
	return -1;
}

string Solution::addBinary(string a, string b) {
	string strRet;
	int iLen_a = a.length(), iLen_b = b.length(), i, j;
	string &str_a = iLen_a > iLen_b ? a : b;
	string &str_b = iLen_b < iLen_a ? b : a;
	if (iLen_a < iLen_b) {
		int tmp = iLen_a;
		iLen_a = iLen_b;
		iLen_b = tmp;
	}
	bool bFlag = false;
	for (i = iLen_a - 1, j = iLen_b - 1; j >= 0; --j, --i) {
		if (str_a[i] == '1' && str_b[j] == '1') {
			if (!bFlag) {
				bFlag = true;
				str_a[i] = '0';
			}
		} else if (str_a[i] ^ str_b[j]) {
			if (bFlag) {
				str_a[i] = '0';
				bFlag = true;
			} else {
				str_a[i] = '1';
			}
		} else {
			if (bFlag) {
				bFlag = false;
				str_a[i] = '1';
			}
		}
	}
	if (bFlag) {
		for (; i >= 0; --i) {
			if (str_a[i] == '1') {
				str_a[i] = '0';
			} else {
				str_a[i] = '1';
				break;
			}
		}
		if (i < 0) {
			string str = "1";
			return str + str_a;
		}
	}
	return str_a;
}

unsigned int Solution::reverseBits(unsigned int n) {
	unsigned int uiTemp = 0;
	for (int i = 0; i < 32; ++i) {
		uiTemp = (uiTemp << 1);
		if (n & 1) {
			uiTemp = uiTemp ^ 0x1;
		}
		n = n >> 1;
	}
	return uiTemp;
}

int Solution::compareVersion(string version1, string version2) {
	int iStart1 = 0, iStart2 = 0;
	int len1 = version1.length(), len2 = version2.length();
	while (1) {
		int iPos1 = version1.find('.', iStart1), iPos2 = version2.find('.', iStart2);
		iPos1 = iPos1 < 0 ? len1 : iPos1;
		iPos2 = iPos2 < 0 ? len2 : iPos2;
		int nStatus = compareInt(version1.c_str() + iStart1, iPos1 - iStart1, version2.c_str() + iStart2, iPos2 - iStart2);
		iStart1 = iPos1 + 1 < len1 ? iPos1 + 1 : len1;
		iStart2 = iPos2 + 1 < len2 ? iPos2 + 1 : len2;
		if (nStatus != 0) {
			return nStatus;
		} else if (iStart1 < version1.length() || iStart2 < version2.length()) {
			continue;
		} else {
			return 0;
		}
	}
	return 0;
}

int Solution::compareInt(const char *str1, int len1, const char *str2, int len2) {
	while (*str1 == '0') {
		++str1; --len1;
	}
	while (*str2 == '0') {
		++str2; --len2;
	}
	if (len1 > len2) {
		return 1;
	} else if (len1 < len2) {
		return -1;
	} else {
		for (int i = 0; i < len1; ++i) {
			if (str1[i] > str2[i]) {
				return 1;
			} else if (str1[i] < str2[i]) {
				return -1;
			}
		}
		return 0;
	}
}

void Solution::rotate(int nums[], int n, int k) {
	if (n == 0) {
		return;
	}
	k = k % n;
	int iPos = 0, iNext = nums[0], tmp;
	for (int i = k, count = 0; count < n; ++count) {
		tmp = nums[i];
		nums[i] = iNext;
		iNext = tmp;
		if (i > iPos) {
			i = (i + k) % n;
		} else {
			iNext = nums[++iPos];
			i = k + ++i;
		}
	}
}

int Solution::trailingZeroes(int n) {
	int iCount = 0;
	while (n != 0) {
		n /= 5;
		iCount += n;
	}
	return iCount;
}

string Solution::convertToTitle(int n) {
	string strRet;
	while (n) {
		if (n % 26 != 0) {
			strRet += (n % 26 + 'A' - 1);
			n /= 26;
		} else {
			strRet += 'Z';
			n = (n - 26) / 26;
		}
	}
	for (int front = 0, rear = strRet.length() - 1; front < rear; ++front, --rear) {
		char ch = strRet[front];
		strRet[front] = strRet[rear];
		strRet[rear] = ch;
	}
	return strRet;
}

bool Solution::isValidSudoku(vector<vector<char> > &board) {
	int judge_row = 0, judge_col = 0, judge_sqr = 0;
	for (int i = 0; i < 9; ++i) {
		judge_row = 0;
		judge_col = 0;
		judge_sqr = 0;
		for (int j = 0; j < 9; ++j) {
			if (board[i][j] != '.') {
				if (judge_row & (0x1 << (board[i][j] - '0'))) {
					return false;
				}
				judge_row = judge_row | (0x1 << (board[i][j] - '0'));
			}
			if (board[j][i] != '.') {
				if (judge_col & (0x1 << (board[j][i] - '0'))) {
					return false;
				}
				judge_col = judge_col | (0x1 << (board[j][i] - '0'));
			}
		}
		for (int row = i / 3 * 3; row < 3 + i / 3 * 3; ++row) {
			for (int col = i % 3 * 3; col < 3 + i % 3 * 3; ++col) {
				if (board[row][col] != '.') {
					if (judge_sqr & (0x1 << (board[row][col] - '0'))) {
						return false;
					}
					judge_sqr = judge_sqr | (0x1 << (board[row][col] - '0'));
				}
			}
		}
	}
	return true;
}

bool Solution::wordBreak(string &s, int pos, unordered_set<string> &dict, bool &flag) {
	int i = pos;
	string str;
	if (pos == s.length() - 1 && dict.find(str + s[s.length() - 1]) == dict.end()) {
		flag = true;
	}
	if (flag) {
		return false;
	}
	for (; i < s.length(); ++i) {
		str = s.substr(pos, i - pos + 1);
		if (dict.find(str) != dict.end()) {
			bool bFlag = i < s.length() - 1 ? wordBreak(s, i + 1, dict, flag) : true;
			if (bFlag) {
				return bFlag;
			}
		}
	}
	return false;
}

bool Solution::wordBreak(string s, unordered_set<string> &dict) {
	bool bFlag = false;
	return wordBreak(s, 0, dict, bFlag);
}

ListNode* Solution::detectCycle(ListNode *head) {
	if (nullptr != head && nullptr != head->next && nullptr != head->next->next) {
		ListNode *fast = head, *slow = head, *tmp;
		int count = 1;
		do {

			if (nullptr == fast || nullptr == fast->next) {
				return NULL;
			}
			slow = slow->next;
			fast = fast->next->next;
			++count;
		} while (fast != slow);
		tmp = slow;
		fast = head;
		int length = 1;
		for (slow = slow->next; slow != tmp; slow = slow->next) {
			++length;
		}
		for (int i = 1; i < (count - length); ++i) {
			fast = fast->next;
		}
		while (fast != tmp) {
			fast = fast->next;
			tmp = tmp->next;
		}
		return fast;
	}
	return NULL;
}

int Solution::numDecodings(string s) {
	int iRet = 1, i, iStart;
	if (s.length() <= 0) {
		return 0;
	}
	if (s.length() == 1) {
		return s[0] == '0' ? 0 : 1;
	}
	for (i = 0, iStart = 0; i < s.length(); ++i) {
		if (s[i] > '2' || s[i] == '0') {
			iRet *= numDecodings_sustr(s.substr(iStart, i - iStart + 1));
			iStart = i + 1;
		} else if (i < s.length() - 1 && s[i] == '2' && s[i + 1] > '6') {
			iRet *= numDecodings_sustr(s.substr(iStart, i - iStart + 1));
			iStart = i + 1;
		}
	}
	if (s[s.length() - 1] <= '2') {
		iRet *= numDecodings_sustr(s.substr(iStart, i - iStart + 1));
	}
	return iRet;
}

int Solution::numDecodings_sustr(string s) {
	if (s.length() <= 0 || s[0] == '0') {
		return 0;
	}
	if (s.length() == 1) {
		return 1;
	}
	if (s.length() == 2) {
		if (s[0] > '2' || (s[0] == '2' && s[1] > '7') || s[1] == '0') {
			return 1;
		} else {
			return 2;
		}
	}
	string str1(&s[1]);
	if (s[0] > '2' || (s[0] == '2' && s[1] > '7') || s[1] == '0') {
		return numDecodings_sustr(str1);
	} else {
		string str2(&s[2]);
		return numDecodings_sustr(str1) + numDecodings_sustr(str2);
	}
}

int Solution::isHave(const char *str, int len, char ch) {
	for (int i = 0; i < len; ++i) {
		if (str[i] == ch) {
			return i;
		}
	}
	return -1;
}

int Solution::lengthOfLongestSubstring(string s) {
	const char *pStr = s.c_str();
	if (s.length() <= 0) {
		return 0;
	}
	int iMax = 1, iCount = 1, iStart = 0;
	for (int i = 1; i < s.length(); ++i) {
		int iTemp = isHave(pStr + iStart, i - iStart, pStr[i]);
		if (iTemp < 0) {
			++iCount;
		} else {
			if (iMax < iCount) {
				iMax = iCount;
			}
			iStart = iStart + iTemp + 1;
			iCount = iCount - iTemp;
		}
	}
	return iCount > iMax ? iCount : iMax;
}

int Solution::sqrt(int x) {
	int temp = 0;
	int v_bit = 15;
	int n = 0;
	int b = 0x8000;
	if (x <= 1) {
		return x;
	}
	do {
		temp = ((n << 1) + b) << (v_bit--);
		if (x >= temp) {
			n += b;
			x -= temp;
		}
	} while (b >>= 1);
	return n;
}

ListNode* Solution::partition(ListNode *&head, int x) {
	ListNode *front1 = nullptr, *rear1 = nullptr, *front2 = nullptr, *rear2 = nullptr, *temp = head;
	if (head == nullptr) {
		return head;
	}
	if (head->val >= x) {
		front2 = head;
		while (temp->next && temp->next->val >= x) {
			temp = temp->next;
		}
		rear2 = temp;
		front1 = temp->next;
		temp = temp->next;
		while (temp) {
			while (temp->next && temp->next->val < x) {
				temp = temp->next;
			}
			rear2->next = temp->next;
			rear1 = temp;
			if (!(temp = temp->next)) {
				break;
			}
			while (temp->next && temp->next->val >= x) {
				temp = temp->next;
			}
			rear2 = temp;
			rear1->next = temp->next;
			if (!(temp = temp->next)) {
				break;
			}
		}
	} else {
		front1 = head;
		while (temp->next && temp->next->val < x) {
			temp = temp->next;
		}
		rear1 = temp;
		front2 = temp->next;
		temp = temp->next;
		while (temp) {
			while (temp->next && temp->next->val >= x) {
				temp = temp->next;
			}
			rear1->next = temp->next;
			rear2 = temp;
			if (!(temp = temp->next)) {
				break;
			}
			while (temp->next && temp->next->val < x) {
				temp = temp->next;
			}
			rear1 = temp;
			rear2->next = temp->next;
			if (!(temp = temp->next)) {
				break;
			}
		}
	}
	if (rear1) {
		rear1->next = front2;
	}
	return front1 ? front1 : front2;
}
ListNode* Solution::partition(ListNode *&head, ListNode *&end, int x) {
	ListNode *front1 = nullptr, *rear1 = nullptr, *front2 = nullptr, *rear2 = nullptr, *temp = head, *next;
	if (head == nullptr) {
		return head;
	}
	if (end == nullptr) {
		next = nullptr;
	} else {
		next = end->next;
		end->next = nullptr;
	}
	if (head->val >= x) {
		front2 = head;
		while (temp->next && temp->next->val >= x) {
			temp = temp->next;
		}
		rear2 = temp;
		front1 = temp->next;
		temp = temp->next;
		while (temp) {
			while (temp->next && temp->next->val < x) {
				temp = temp->next;
			}
			rear2->next = temp->next;
			rear1 = temp;
			if (!(temp = temp->next)) {
				break;
			}
			while (temp->next && temp->next->val >= x) {
				temp = temp->next;
			}
			rear2 = temp;
			rear1->next = temp->next;
			if (!(temp = temp->next)) {
				break;
			}
		}
	} else {
		front1 = head;
		while (temp->next && temp->next->val < x) {
			temp = temp->next;
		}
		rear1 = temp;
		front2 = temp->next;
		temp = temp->next;
		while (temp) {
			while (temp->next && temp->next->val >= x) {
				temp = temp->next;
			}
			rear1->next = temp->next;
			rear2 = temp;
			if (!(temp = temp->next)) {
				break;
			}
			while (temp->next && temp->next->val < x) {
				temp = temp->next;
			}
			rear1 = temp;
			rear2->next = temp->next;
			if (!(temp = temp->next)) {
				break;
			}
		}
	}
	if (rear1) {
		rear1->next = front2;
	}
	head = front1 ? front1 : front2;
	end = rear2 ? rear2 : rear1;
	return rear1;
}
ListNode* Solution::sortList(ListNode *&head, ListNode *&end) {
	ListNode *pMid, *pHead = head, *pEnd = end, *pTemp;
	if (nullptr == head || head == end) {
		return head;
	}
	int iTemp = head->val;
	pMid = partition(pHead, pEnd, iTemp);
	if (pMid != nullptr) {
		sortList(pHead, pTemp);
		pMid = pMid->next;
	} else {
		pMid = pHead;
	}
	pTemp = pMid;
	if (pMid != nullptr && pMid->next != nullptr) {
		pMid = pMid->next;
		sortList(pMid, pEnd);
		pTemp->next = pMid;
	}
	head = pHead;
	end = pEnd;
	return head;
}

ListNode* Solution::sortList(ListNode *head) {
	if (head == nullptr) {
		return nullptr;
	}
	ListNode *pHead = head, *pEnd = nullptr, *pMid;
	return sortList(pHead, pEnd);
}

vector<vector<int>> Solution::isPathSum(TreeNode *root, int sum) {
	bool bFlag = false;
	vector<vector<int>> vec2Ret;
	if (root == nullptr) {
		return vec2Ret;
	}
	if (root->left == nullptr && root->right == nullptr && root->val == sum) {
		vector<int> vecTemp;
		vecTemp.push_back(root->val);
		vec2Ret.push_back(vecTemp);
		return vec2Ret;
	}
	vector<vector<int>> vec2Left = isPathSum(root->left, sum - root->val);
	for (auto iter = vec2Left.begin(); iter != vec2Left.end(); ++iter) {
		iter->push_back(root->val);
	}
	vector<vector<int>> vec2Right = isPathSum(root->right, sum - root->val);
	vector<vector<int>> &vec2Temp = vec2Left.size() > 0 ? vec2Left : vec2Right;
	for (auto iter = vec2Right.begin(); iter != vec2Right.end(); ++iter) {
		iter->push_back(root->val);
		if (vec2Left.size() > 0) {
			vec2Left.push_back(*iter);
		}
	}
	return vec2Temp;
}

vector<vector<int>> Solution::pathSum(TreeNode *root, int sum) {
	vector<vector<int>> vec2Ret = isPathSum(root, sum);
	for (auto iter = vec2Ret.begin(); iter != vec2Ret.end(); ++iter) {
		int *p = &((*iter)[0]), temp;
		for (int i = 0, j = iter->size() - 1; i < j; ++i, --j) {
			temp = p[i];
			p[i] = p[j];
			p[j] = temp;
		}
	}
	return vec2Ret;
}


int Solution::minPathSum(vector<vector<int>> &grid, int row, int col) {
	int iRet = 0;
	if (vec2[row][col] != -1) {
		return vec2[row][col];
	}
	if (row == grid.size() - 1) {
		for (auto iter = grid[row].begin() + col; iter != grid[row].end(); ++iter) {
			iRet += *iter;
		}
	} else if (col == grid[row].size() - 1) {
		for (int i = row; i < grid.size(); ++i) {
			iRet += grid[i][col];
		}
	} else {
		int iDown = minPathSum(grid, row + 1, col), iRight = minPathSum(grid, row, col + 1);
		iRet = grid[row][col] + (iDown < iRight ? iDown : iRight);
	}
	vec2[row][col] = iRet;
	return iRet;
}

int Solution::minPathSum(vector<vector<int> > &grid) {
	vec2.resize(grid.size());
	for (int i = 0; i < grid.size(); ++i) {
		vec2[i].resize(grid[0].size(), -1);
	}
	return minPathSum(grid, 0, 0);
}
// improved method
int Solution::improve_minPathSum(vector<vector<int> > &grid) {
	if (grid.size() <= 0) {
		return 0;
	}
	for (int i = 1; i < grid.size(); ++i) {
		grid[i][0] += grid[i - 1][0];
	}
	for (int i = 1; i < grid[0].size(); ++i) {
		grid[0][i] += grid[0][i - 1];
	}
	for (auto iter = grid.begin() + 1; iter != grid.end(); ++iter) {
		int *pre = &(*(iter - 1))[0], *p = &(*iter)[0];
		for (int i = 1; i < iter->size(); ++i) {
			p[i] += (p[i - 1] < pre[i] ? p[i - 1] : pre[i]);
		}
	}
	return grid[grid.size() - 1][grid[0].size() - 1];
}

string Solution::simplifyPath(string path) {
	int iEnd = path.length(), iStart = 0, iCount = 0;
	string strRet;
	while (path[--iEnd] == '/') {}
	for (int i = iEnd; i >= 0; --i) {
		string str;
		while (i >= 0 && path[i] == '/') {
			--i;
		}
		iStart = i;
		while (i >= 0 && path[i] != '/') {
			--i;
		}
		str = path.substr(i + 1, iStart - i);
		if (str == "..") {
			iCount++;
		} else if (str != "." && str.length() > 0) {
			if (iCount == 0) {
				strRet = "/" + str + strRet;
				continue;
			}
			--iCount;
		}
	}
	return strRet.length() > 0 ? strRet : "/";
}

string Solution::simplifyPath1(string path) {
	const char* p = path.c_str();
	string res = "/";
	vector<string> full_path;
	char* addr = strtok((char*)p, "/");
	int cur = 0, size = 0;
	while (addr) {
		if (strcmp(addr, ".") == 0) {
		} else if (strcmp(addr, "..") == 0) {
			cur > 0 ? cur-- : cur;
		} else {
			if (cur == size) {
				full_path.push_back(addr);
				cur++;
				size++;
			} else {
				full_path[cur++] = addr;
			}
		}
		addr = strtok(NULL, "/");
	}
	for (int i = 0; i<cur; i++) {
		res = res + full_path[i] + "/";
	}
	return res.size() == 1 ? res : res.substr(0, res.size() - 1);
}

TreeNode* Solution::flatten1(TreeNode *root) {
	if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
		return root;
	}
	if (root->left == nullptr) {
		return flatten1(root->right);
	} else if (root->right == nullptr) {
		root->right = root->left;
		root->left = nullptr;
		return flatten1(root->right);
	} else {
		TreeNode *pTemp = root->right, *pEnd = flatten1(root->left);
		root->right = root->left;
		root->left = nullptr;
		pEnd->right = pTemp;
		return flatten1(pTemp);
	}
}

void Solution::flatten(TreeNode *root) {
	flatten1(root);
}

vector<int> Solution::rightSideView(TreeNode *root) {
	vector<int> vecRet;
	if (NULL == root) {
		return vecRet;
	}
	queue<TreeNode *> queueRoot;
	TreeNode *pPre = root, *pNext;
	queueRoot.push(root);
	queueRoot.push(NULL);
	while (1) {
		pNext = queueRoot.front();
		queueRoot.pop();
		if (NULL == pNext) {
			vecRet.push_back(pPre->val);
			if (queueRoot.empty()) {
				break;
			}
			queueRoot.push(NULL);
			continue;
		}
		if (pNext->left) {
			queueRoot.push(pNext->left);
		}
		if (pNext->right) {
			queueRoot.push(pNext->right);
		}
		pPre = pNext;
	}
	return vecRet;
}

ListNode* Solution::removeElements(ListNode* head, int val) {
	ListNode *pTemp = head, *pre = head;
	while (pTemp) {
		if (pTemp->val == val) {
			if (pTemp == head) {
				head = pTemp->next;
				pTemp = head;
			} else {
				pre->next = pTemp->next;
				pTemp = pTemp->next;
			}
			delete pTemp;
		}
		pre = pTemp;
		pTemp = pTemp->next;
	}
	return head;
}

bool Solution::isHappy(int n) {
	unordered_set<int> setSum;
	setSum.insert(n);
	while (1) {
		int iSum = 0;
		while (n) {
			iSum += (n % 10) * (n % 10);
			n /= 10;
		}
		if (iSum == 1) {
			return true;
		} else if (setSum.find(iSum) != setSum.end()) {
			return false;
		} else {
			setSum.insert(iSum);
			n = iSum;
		}
	}
}

vector<vector<int> > Solution::zigzagLevelOrder(TreeNode *root) {
	queue<TreeNode *> queRoot;
	vector<vector<int>> vec2Ret;
	bool bFlag = true;
	if (NULL == root) {
		return vec2Ret;
	}
	vector<int> vec;
	queRoot.push(root);
	queRoot.push(NULL);
	while (1) {
		root = queRoot.front();
		queRoot.pop();
		if (root != NULL) {
			vec.push_back(root->val);
			if (root->right != NULL) {
				queRoot.push(root->right);
			}
			if (root->left != NULL) {
				queRoot.push(root->left);
			}
		} else {
			if (bFlag) {
				int front = 0, end = vec.size() - 1, *p = &(vec[0]), temp;
				while (front < end) {
					temp = p[front];
					p[front] = p[end];
					p[end] = temp;
					++front;
					--end;
				}
			}
			bFlag = !bFlag;
			vec2Ret.push_back(vec);
			vec.clear();
			if (queRoot.empty()) {
				break;
			}
			queRoot.push(NULL);
		}
	}
	return vec2Ret;
}

ListNode* Solution::rotateRight(ListNode* head, int k) {
	ListNode *pre = head, *back = head;
	if (pre == NULL) {
		return head;
	}
	for (int i = 0; i < k; ++i) {
		pre = pre->next;
		if (pre == NULL) {
			k = i + k % (i + 1) + 1;
			pre = head;
		}
	}
	if (pre == NULL) {
		return head;
	}
	while (pre->next) {
		pre = pre->next;
		back = back->next;
	}
	pre->next = head;
	head = back->next;
	back->next = NULL;
	return head;
}
/*
string Solution::largestNumber(vector<int>& nums) {
	string strRet;
	if (nums.size() <= 0) {
		return strRet;
	}
	vector<vector<string>> vec2;
	int iCountZeros;
	vec2.resize(0);
	for (auto it = nums.begin(); it != nums.end(); ++it) {
		int temp = *it, high = temp;
		string str;
		str += '0' + (temp % 10);
		while (temp /= 10) {
			high = temp;
			str += (temp % 10);
		}
		if (high == 0) {
			++iCountZeros;
		}
		vec2[high - 1].push_back(str);
	}
	for (auto it = vec2.begin(); it != vec2.end(); ++it) {
		;
	}
}*/

ListNode* Solution::deleteDuplicates1(ListNode* head) {
	if (head == NULL) {
		return head;
	}
	unordered_map<int, bool> mapFlag;
	ListNode *temp = head, *end = NULL, *p;
	while (temp) {
		auto it = mapFlag.find(temp->val);
		if (it != mapFlag.end()) {
			it->second = true;
		} else {
			mapFlag[temp->val] = false;
		}
		temp = temp->next;
	}
	temp = head;
	while (temp && mapFlag[temp->val]) {
		head = temp;
		temp = temp->next;
		delete head;
	}
	if (temp == NULL) {
		return NULL;
	}
	head = temp;
	end = temp;
	temp = temp->next;
	while (temp) {
		if (mapFlag[temp->val]) {
			p = temp;
			temp = temp->next;
			delete p;
		} else {
			end->next = temp;
			end = end->next;
			temp = temp->next;
		}
	}
	end->next = NULL;
	return head;
}

ListNode* Solution::deleteDuplicates(ListNode* head) {
	if (!head) {
		return head;
	}
	ListNode temp(0), *cur = head->next, *subhead = &temp;
	subhead->next = head;
	while (1) {
		ListNode *p = subhead->next, *pFlag;
		cur = p->next;
		pFlag = cur;
		while (cur && cur->val == p->val) {
			cur = cur->next;
			subhead->next = cur;
		}
		if (!cur) {
			if (subhead->next) {
				subhead->next->next = NULL;
			}
			break;
		} else if (cur != p->next) {
			subhead->next = cur;
		} else {
			subhead = p;
		}
	}
	return temp.next;
}

int Solution::canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
	int n = gas.size();
	if (n <= 0) {
		return -1;
	}
	int *pGas = &(gas[0]), *pCost = &(cost[0]);
	int iSum = pGas[0] - pCost[0], iMin = 0, iRet = iSum < 0 ? 1 : 0;
	for (int i = 1; i < n; ++i) {
		iSum = iSum + pGas[i] - pCost[i];
		if (iMin > iSum) {
			iMin = iSum;
			iRet = i + 1;
		}
	}
	return iSum >= 0 ? iRet : -1;
}

UndirectedGraphNode* Solution::cloneGraph(UndirectedGraphNode *node) {
	if (node == NULL) {
		return NULL;
	}
	UndirectedGraphNode *pRet = new UndirectedGraphNode(node->label);
	old.insert(node);
	for (auto it = (node->neighbors).begin(); it != (node->neighbors).end(); ++it) {
		unordered_set<UndirectedGraphNode *>::iterator it_find = old.find(*it);
		if (it_find == old.end()) {
			(pRet->neighbors).push_back(cloneGraph(*it));
		} else {
			(pRet->neighbors).push_back(*it_find);
		}
	}
	return pRet;
}

bool Solution::isPalindrome(string &str, int start, int end) {
	while (start < end && str[start] == str[end]) {
		++start;
		--end;
	}
	return start >= end ? true : false;
}

void Solution::partition(string &s, int index, vector<string> &cur, vector<vector<string>> &vec2Ret) {
	if (index == s.length()) {
		vec2Ret.push_back(cur);
		return;
	}
	for (int i = index; i < s.size(); ++i) {
		if (isPalindrome(s, index, i)) {
			cur.push_back(s.substr(index, i - index + 1));
			partition(s, i + 1, cur, vec2Ret);
			cur.pop_back();
		}
	}
}

vector<vector<string>> Solution::partition(string s) {
	vector<vector<string>> vec2Ret;
	vector<string> cur;
	partition(s, 0, cur, vec2Ret);
	return vec2Ret;
}

void Solution::quickSort_three(int *num, int len) {
	int iStart = 0, iEnd = len - 1;
	int tmp = num[0];
	if (iStart >= iEnd) {
		return;
	}
	while (iStart < iEnd) {
		while (iStart < iEnd && num[iEnd] > tmp) {
			--iEnd;
		}
		num[iStart] = num[iEnd];
		while (iStart < iEnd && num[iStart] <= tmp) {
			++iStart;
		}
		num[iEnd] = num[iStart];
	}
	num[iStart] = tmp;
	quickSort_three(num, iStart);
	quickSort_three(num + iStart + 1, len - iStart - 1);
}

int Solution::binarySearch_three(vector<int> &num, int data, int start) {
	int iStart = start, iEnd = num.size() - 1;
	if (iStart > iEnd) {
		return -1;
	}
	if (iStart == iEnd) {
		return num[iStart] == data ? 0 : num[iStart] - data;
	}
	int iMid;
	while (iStart <= iEnd) {
		iMid = (iStart + iEnd) / 2;
		if (num[iMid] < data) {
			iStart = iMid + 1;
		} else if (num[iMid] > data) {
			iEnd = iMid - 1;
		} else {
			return 0;
		}
	}
	if (iEnd < start) {
		return num[iStart] - data;
	} else if (iStart >= num.size()) {
		return num[iEnd] - data;
	} else {
		int s = num[iStart] - data, e = num[iEnd] - data;
		return abs(s) < abs(e) ? s : e;
	}
}

int Solution::threeSumClosest(vector<int>& nums, int target) {
	int iRet = INT_MAX - target, length = nums.size();
	int *pArray = &(nums[0]);
	sort(nums.begin(), nums.end());
	for (int i = 0; i < length - 2; ++i) {
		int start = i + 1, end = length - 1;
		int sum = pArray[i] + pArray[start] + pArray[start + 1];
		if (sum > target) {
			iRet = abs(sum - target) < abs(iRet - target) ? sum : iRet;
			return iRet;
		}
		while (start < end) {
			sum = pArray[i] + pArray[start] + pArray[end];
			int temp = iRet - target, abs_value = temp < 0 ? -temp : temp;
			if (sum != target) {
				if (sum > target) {
					if (sum - target < abs_value) {
						iRet = sum;
					}
					--end;
				} else {
					if (target - sum < abs_value) {
						iRet = sum;
					}
					++start;
				}
			} else {
				return target;
			}
		}
	}
	return iRet;
}

int Solution::threeSumClosest1(vector<int>& num, int target) {
	int iRet = INT_MAX - target;
	quickSort_three(&num[0], num.size());
	int tmp1 = num[0] + 1;
	for (int i = 0; i < num.size() - 1; ++i) {
		if (num[i] == tmp1) {
			continue;
		}
		int tmp2 = num[i + 1] + 1;
		for (int j = i + 1; j < num.size() - 1; ++j) {
			if (num[j] == tmp2) {
				continue;
			}
			int d = binarySearch_three(num, target - (num[i] + num[j]), j + 1);
			if (abs(target - iRet) > abs(d)) {
				iRet = target + d;
			}
			tmp2 = num[j];
		}
		tmp1 = num[i];
	}
	return iRet;
}

int Solution::countPrimes(int n) {
	if (n <= 2) return 0;
	int N = n - 1;
	int M = N / 2 + N % 2;
	int iCount = n / 2;
	bool* index = new bool[M];

	for (int i = 0; i<M; i++) {
		index[i] = true;
	}
	index[0] = false;

	for (int div = 3; div <= sqrt(N); div += 2) {
		if (index[div >> 1]) {
			for (int j = div + (div >> 1); j<M; j += div) {
				if (index[j]) {
					index[j] = false;
					--iCount;
				}
			}
		}
	}
	delete[] index;
	return iCount;
}

void Solution::solve(vector<vector<char>> &board) {
	if (board.size() <= 1) {
		return;
	}
	for (auto it_row = board.begin() + 1; it_row < board.end() - 1; ++it_row) {
		auto pre = it_row - 1;
		for (auto it_col = it_row->begin() + 1; it_col < it_row->end() - 1; ++it_col) {
			if (*it_col == 'O') {
				if (*(it_col - 1) != 'O' && *(pre->begin() + (it_col - it_row->begin())) != 'O') {
					*it_col = '*';
				}
			}
		}
		for (auto it_col = it_row->end() - 2; it_col > it_row->begin(); --it_col) {
			if (*it_col == '*' && *(it_col + 1) != 'X') {
				*it_col = *(it_col + 1);
			}
		}
	}
	for (auto it_row = board.end() - 2; it_row > board.begin(); --it_row) {
		auto pre = it_row + 1, next = it_row - 1;
		for (auto it_col = it_row->end() - 2; it_col > it_row->begin(); --it_col) {
			if (*it_col == '*') {
				if (*(pre->begin() + (it_col - it_row->begin())) == 'O' || *(it_col + 1) == 'O') {
					*it_col = 'O';
				}
			}
		}
		for (auto it_col = it_row->begin() + 1; it_col != it_row->end(); ++it_col) {
			if (*it_col == '*') {
				if (*(it_col - 1) == 'O' || *(next->begin() + (it_col - it_row->begin())) != '*') {
					*it_col = *(it_col - 1);
				}
			}
		}
	}
	for (auto it_row = board.begin() + 1; it_row < board.end() - 1; ++it_row) {
		auto pre = it_row - 1;
		for (auto it_col = it_row->begin() + 1; it_col < it_row->end() - 1; ++it_col) {
			if (*it_col == '*') {
				if (*(it_col - 1) == 'O' || *(pre->begin() + (it_col - it_row->begin())) == 'O') {
					*it_col = 'O';
				} else {
					*it_col = 'X';
				}
			}
		}
	}
}

void Solution::combinationSum(vector<int> &cur, vector<vector<int>> &vec2Res, vector<int> &candidates, vector<int>::iterator index, int target) {
	if (target < 0) {
		return;
	}
	if (target == 0) {
		vec2Res.push_back(cur);
	}
	for (auto it = index; it != candidates.end(); ++it) {
		if (*it <= target) {
			cur.push_back(*it);
			combinationSum(cur, vec2Res, candidates, it, target - *it);
			cur.pop_back();
		} else {
			break;
		}
	}
}

vector<vector<int> > Solution::combinationSum(vector<int> &candidates, int target) {
	sort(candidates.begin(), candidates.end());
	vector<vector<int>> vec2Ret;
	vector<int> cur;
	combinationSum(cur, vec2Ret, candidates, candidates.begin(), target);
	return vec2Ret;
}

bool Solution::isIsomorphic(string s, string t) {
	char map1[256], map2[256];
	for (int i = 0; i < 256; ++i) {
		map1[i] = 0;
		map2[i] = 0;
	}
	if (s.length() != t.length()) {
		return false;
	}
	for (int i = 0; i < t.length(); ++i) {
		if (map1[s[i]] == 0) {
			if (map2[t[i]] != 0) {
				return false;
			}
			map1[s[i]] = t[i];
			map2[t[i]] = s[i];
		} else if (map1[s[i]] != t[i]) {
			return false;
		}
	}
	return true;
}

int Solution::rangeBitwiseAnd(int m, int n) {
	int iRet = m, tmp = ~0;
	do {
		iRet &= tmp;
		tmp <<= 1;
	} while ((n & tmp) > m);
	return iRet;
}

int Solution::minimumTotal(vector<vector<int>> &triangle, int row, int col) {
	if (col >= triangle[row].size()) {
		return INT_MAX;
	}
	if (row == triangle.size() - 1) {
		return triangle[row][col];
	}
	int iRight = minimumTotal(triangle, row + 1, col), iLeft = minimumTotal(triangle, row + 1, col + 1);
	return triangle[row][col] + (iRight < iLeft ? iRight : iLeft);
}

int Solution::minimumTotal(vector<vector<int> > &triangle) {
	return minimumTotal(triangle, 0, 0);
}

void Solution::reorderList(ListNode* head) {
	if (head == NULL || head->next == NULL) {
		return;
	}
	ListNode *fast = head, *slow = head, *tmp;
	while (fast) {
		fast = fast->next;
		if (!fast) {
			break;
		}
		fast = fast->next;
		slow = slow->next;
	}
	fast = slow->next;
	slow->next = NULL;
	slow = NULL;
	while (fast) {
		tmp = fast->next;
		fast->next = slow;
		slow = fast;
		fast = tmp;
	}
	fast = head;
	while (slow) {
		tmp = fast->next;
		fast->next = slow;
		fast = tmp;
		tmp = slow->next;
		slow->next = fast;
		slow = tmp;
	}
}

bool Solution::isValidBST(TreeNode* root, int &min, int &max) {
	bool bRet = true;
	min = INT_MAX;
	max = INT_MIN;
	if (root != NULL && bFlag) {
		int leftMin = INT_MAX, leftMax = INT_MIN, rightMin = INT_MAX, rightMax = INT_MIN;
		bRet = isValidBST(root->left, leftMin, leftMax) && isValidBST(root->right, rightMin, rightMax);;
		if (root->left != NULL) {
			bRet = bRet && leftMax < root->val;
		}
		if (root->right != NULL) {
			bRet = bRet && rightMin > root->val;
		}
		bFlag = bRet;
		min = leftMin < root->val ? leftMin : root->val;
		max = rightMax > root->val ? rightMax : root->val;
	}
	return bRet;
}

bool Solution::isValidBST(TreeNode* root) {
	bFlag = true;
	int min, max;
	return isValidBST(root, min, max);
}

TreeNode* Solution::sortedListToBST(ListNode* head) {
	if (!head) {
		return NULL;
	}
	ListNode *fast = head, **slow = &head;
	while (fast) {
		fast = fast->next;
		if (!fast) {
			break;
		}
		fast = fast->next;
		slow = &((*slow)->next);
	}
	fast = *slow;
	*slow = NULL;
	TreeNode *root = new TreeNode(fast->val);
	root->left = sortedListToBST(head);
	root->right = sortedListToBST(fast->next);
	return root;
}

ListNode* Solution::insertionSortList(ListNode* head) {
	if (!head) {
		return NULL;
	}
	ListNode h(0);
	h.next = head;
	ListNode *pEnd = head->next, **pTmp, *p;
	head->next = NULL;
	while (pEnd) {
		pTmp = &(h.next);
		while (*pTmp && (*pTmp)->val < pEnd->val) {
			pTmp = &((*pTmp)->next);
		}
		p = pEnd->next;
		pEnd->next = *pTmp;
		*pTmp = pEnd;
		pEnd = p;
	}
	return h.next;
}

ListNode* Solution::merge2Lists(ListNode* l1, ListNode* l2) {
	ListNode list(0), *pRet = &list;
	while (l1 && l2) {
		if (l1->val < l2->val) {
			pRet->next = l1;
			l1 = l1->next;
		} else {
			pRet->next = l2;
			l2 = l2->next;
		}
		pRet = pRet->next;
	}
	pRet->next = l1 ? l1 : l2;
	return list.next;
}

ListNode* Solution::mergeKLists(vector<ListNode*>& lists) {
	int size = lists.size();
	if (size < 1) {
		return NULL;
	}
	while (size > 1) {
		for (int i = 0; i < size / 2; ++i) {
			lists[i] = merge2Lists(lists[2 * i], lists[2 * i + 1]);
		}
		if (size % 2) {
			lists[size / 2] = lists[size - 1];
		}
		size = size / 2 + size % 2;
	}
	return lists[0];
}

void Solution::reverseWords(string &s) {
	stack<string> stack_str;
	int length = s.length(), front = 0, rear = length - 1, index = 0;
	while (1) {
		while (front < length && s[front] == ' ') {
			++front;
		}
		rear = front + 1;
		while (rear < length && s[rear] != ' ') {
			++rear;
		}
		if (front < length) {
			stack_str.push(s.substr(front, rear - front));
			front = rear;
		} else {
			break;
		}
	}
	s = "";
	while (!stack_str.empty()) {
		if (s.empty()) {
			s = stack_str.top();
		} else {
			s += ' ' + stack_str.top();
		}
		stack_str.pop();
	}
}

int Solution::evalRPN(vector<string>& tokens) {
	stack<int> st;
	for (auto it = tokens.begin(); it != tokens.end(); ++it) {
		if (it->length() > 1 || ((*it)[0] <= '9' && (*it)[0] >= '0')) {
			st.push(atoi(it->c_str()));
		} else {
			int tmp = st.top();
			st.pop();
			switch ((*it)[0]) {
			case '+':
				st.top() += tmp;
				break;
			case '-':
				st.top() -= tmp;
				break;
			case '*':
				st.top() *= tmp;
				break;
			case '/':
				st.top() /= tmp;
				break;
			}
		}
	}
	return st.top();
}

bool Solution::containsNearbyDuplicate(vector<int>& nums, int k) {
	unordered_map<int, vector<int>::iterator> map_va2in;
	for (auto it = nums.begin(); it != nums.end(); ++it) {
		auto it_f = map_va2in.find(*it);
		if (it_f == map_va2in.end()) {
			map_va2in[*it] = it;
		} else {
			if (it - it_f->second <= k) {
				return true;
			}
			map_va2in[*it] = it;
		}
	}
	return false;
}

int Solution::minSubArrayLen(int s, vector<int>& nums) {
	int iWidth = INT_MAX, sum = 0, iCount = 0;
	for (auto it = nums.begin(); it != nums.end(); ++it, ++iCount) {
		sum += *it;
		while (sum >= s) {
			sum -= *(it - iCount);
			if (iCount < iWidth) {
				iWidth = iCount;
			}
			--iCount;
		}
	}
	return iWidth + 1 > 0 ? iWidth : 0;
}

int Solution::kthSmallest(TreeNode* root, int k) {
	if (root == NULL) {
		return false;
	}
	int iCount = 0;
	stack<TreeNode*> stack;
	stack.push(root);
	TreeNode *pTmp = root;
	while (pTmp) {
		stack.push(pTmp);
		pTmp = pTmp->left;
	}
	while (!stack.empty()) {
		pTmp = stack.top();
		stack.pop();
		if (++iCount == k) {
			return pTmp->val;
		}
		pTmp = pTmp->right;
		while (pTmp) {
			stack.push(pTmp);
			pTmp = pTmp->left;
		}
	}
}


bool Solution::DFS(map<int, vector<int>>::iterator &itStart, map<int, vector<int>> &map, const int &iLable) {
	if (!map.empty() && itStart->second[0] == UNREAD) {
		itStart->second[0] = iLable;
		for (auto it = (itStart->second).begin() + 1; it != (itStart->second).end(); ++it) {
			auto iFind = map.find(*it);
			if (iFind != map.end() && (iFind->second[0] == iLable || !DFS(iFind, map, iLable))) {
				return false;
			}
		}
	}
	return true;
}

bool Solution::canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
	map<int, vector<int>> map;
	for (auto it = prerequisites.begin(); it != prerequisites.end(); ++it) {
		auto mIt = map.find(it->first);
		if (mIt == map.end()) {
			map[it->first].push_back(UNREAD);
		}
		map[it->first].push_back(it->second);
	}
	for (auto it = map.begin(); it != map.end(); ++it) {
		if (!DFS(it, map, it->first)) {
			return false;
		}
	}
	return true;
}

int Solution::calculate(string s) {
	stringstream ss;
	ss << s;
	stack<int> stackData;
	stack<char> stackOpt;
	int iData, iTmp = 0;
	char chOpt;
	ss >> iData;
	stackData.push(iData);
	while (ss >> chOpt) {
		if (chOpt == '/') {
			iTmp = stackData.top();
			stackData.pop();
			ss >> iData;
			stackData.push(iTmp / iData);
		} else if (chOpt == '*') {
			iTmp = stackData.top();
			stackData.pop();
			ss >> iData;
			stackData.push(iTmp * iData);
		} else {
			if (!stackOpt.empty()) {
				iTmp = stackData.top();
				stackData.pop();
				if (stackOpt.top() == '+') {
					stackData.top() += iTmp;
				} else {
					stackData.top() -= iTmp;
				}
			}
			ss >> iData;
			stackData.push(iData);
			stackOpt.push(chOpt);
		}
	}
	if (!stackOpt.empty()) {
		iTmp = stackData.top();
		stackData.pop();
		if (stackOpt.top() == '+') {
			stackData.top() += iTmp;
		} else {
			stackData.top() -= iTmp;
		}
	}
	return stackData.top();
}

bool Solution::lowestCommonAncestor(TreeNode* root, TreeNode* &p, vector<TreeNode*> &vec) {
	if (root != NULL) {
		vec.push_back(root);
		if (root == p) {
			return true;
		}
		if (lowestCommonAncestor(root->left, p, vec)) {
			return true;
		}
		if (lowestCommonAncestor(root->right, p, vec)) {
			return true;
		}
		vec.pop_back();
	}
	return false;
}

TreeNode* Solution::lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (root == NULL) {
		return root;
	}
	vector<TreeNode*> vec1, vec2;
	lowestCommonAncestor(root, p, vec1);
	lowestCommonAncestor(root, q, vec2);
	int index = 0;
	while (index < vec1.size() && index < vec2.size() && vec1[index] == vec2[index]) {
		++index;
	}
	if (index == vec1.size() && vec1[index - 1] != vec2[index - 1]) {
		return NULL;
	}
	return vec1[index - 1];
}

int Solution::countNodes(TreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	stack<TreeNode*> stackLeft, stackRight;
	TreeNode *pTmp = root;
	int ilevelLeft = 0, iLevelRight = 0;
	while (pTmp) {
		++ilevelLeft;
		stackLeft.push(pTmp);
		pTmp = pTmp->left;
	}
	pTmp = root;
	while (pTmp) {
		++iLevelRight;
		stackLeft.push(pTmp);
		pTmp = pTmp->right;
	}
	if (ilevelLeft == iLevelRight) {
		return 0x1 << ilevelLeft - 1;
	}

}

void Solution::letterCombinations(string &digits, int index, vector<string> &vec) {
	if (index >= digits.length()) {
		return;
	}
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		it->push_back(strArray[digits[index] - '0'][0]);
	}
	int iLen = vec.size();
	string &str = strArray[digits[index] - '0'];
	for (int i = 1; i < str.length(); ++i) {
		for (int j = 0; j < iLen; ++j) {
			string strTmp = vec[j];
			strTmp[strTmp.length() - 1] = str[i];
			vec.push_back(strTmp);
		}
	}
	if (digits.length() > index) {
		letterCombinations(digits, index + 1, vec);
	}
}

vector<string> Solution::letterCombinations(string digits) {
	vector<string> vecRet;
	if (digits.length() > 0) {
		vecRet.resize(1);
		letterCombinations(digits, 0, vecRet);
	}
	return vecRet;
}

bool Solution::searchMatrix(vector<vector<int>>& matrix, int target) {
	int m = matrix.size(), n = matrix[0].size(), iStart, iEnd, iMid, iRow = 0, iCol = n - 1;
	if (target < matrix[0][0]) {
		return false;
	}
	while (iRow < m && iCol >= 0) {
		iStart = 0;
		iEnd = iCol;
		while (iStart <= iEnd) {
			iMid = (iStart + iEnd) / 2;
			if (matrix[iRow][iMid] < target) {
				iStart = iMid + 1;
			} else if (matrix[iRow][iMid] > target) {
				iEnd = iMid - 1;
			} else {
				return true;
			}
		}
		iCol = iEnd < 0 ? 0 : iEnd;
		if (++iRow >= m) {
			return false;
		}
		iStart = iRow;
		iEnd = m - 1;
		while (iStart <= iEnd) {
			iMid = (iStart + iEnd) / 2;
			if (matrix[iMid][iCol] < target) {
				iStart = iMid + 1;
			} else if (matrix[iMid][iCol] > target) {
				iEnd = iMid - 1;
			} else {
				return true;
			}
		}
		iRow = iStart > n ? n : iStart;
		iCol--;
	}
	return false;
}

int Solution::countDigitOne(int n) {
	if (n <= 0) {
		return 0;
	}
	stringstream ss;
	string str, strTmp;
	ss << n;
	ss >> str;
	int count = 0, iRet = 0;
	while (n) {
		n /= 10;
		++count;
	}
	for (int i = count - 1; i >= 0; --i) {
		ss.clear();
		if (str[i] == '0') {
			ss << str.substr(0, i);
			ss >> n;
			--n;
			for (int j = 0; j < count - i - 1; ++j) {
				n = n * 10 + 9;
			}// + str.substr(i + 1, count - i - 1);
		} else if (str[i] == '1') {
			strTmp = str.substr(0, i) + str.substr(i + 1, count - i - 1);
			ss << strTmp;
			ss >> n;
		} else {
			strTmp = str.substr(0, i);
			if (strTmp != "") {
				ss << strTmp;
				ss >> n;
			} else {
				n = 0;
			}
			for (int j = 0; j < count - i - 1; ++j) {
				n = n * 10 + 9;
			}
		}
		iRet += n + 1;
	}
	return iRet;
}

vector<string> Solution::generateParenthesis(int n) {
	vector<string> vecRet;
	if (n == 1) {
		vecRet.push_back("()");
		return vecRet;
	}
	for (int i = 0; i < n; ++i) {
		vector<string> vec1 = generateParenthesis(i), vec2 = generateParenthesis(n - i - 1);
		if (vec1.size() <= 0) {
			for (auto i = vec2.begin(); i != vec2.end(); ++i) {
				vecRet.push_back("()" + *i);
			}
			continue;
		}
		for (auto it = vec1.begin(); it != vec1.end(); ++it) {
			if (vec2.size() <= 0) {
				vecRet.push_back("(" + *it + ")");
				continue;
			}
			for (auto i = vec2.begin(); i != vec2.end(); ++i) {
				vecRet.push_back("(" + *it + ")" + *i);
			}
		}
	}
	return vecRet;
}

int Solution::uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	return 0;
}

vector<int> Solution::productExceptSelf(vector<int>& nums) {
	vector<int> vecRet(nums.size());
	int pre = 1, *pNums = &nums[0], *pRet = &vecRet[0], len = nums.size();


	for (int i = 0; i < len; ++i) {
		pRet[i] = pre;
		pre *= pNums[i];
	}
	pre = 1;
	for (int i = len - 1; i >= 0; --i) {
		pRet[i] *= pre;
		pre *= pNums[i];
	}
	return vecRet;
}

vector<int> Solution::majorityElement(vector<int>& nums) {
	if (nums.size() < 1) {
		return vector<int>();
	}
	int a = nums[0], b = a, a_count = 0, b_count = 0;
	bool flag = true;
	for (auto it = nums.begin(); it != nums.end(); ++it) {
		if (a == *it) {
			a_count += 2;
		} else if (b == *it) {
			b_count += 2;
		} else {
			if (--a_count == 0) {
				a = *it;
			}
			if (--b_count == 0) {
				b = *it;
			}
		}
	}
	a_count = b_count = 0;
	for (auto it = nums.begin(); it != nums.end(); ++it) {
		if (*it == a) {
			++a_count;
		} else if (*it == b) {
			++b_count;
		}
	}
	vector<int> ret;
	if (a_count > nums.size() / 3) {
		ret.push_back(a);
	}
	if (b_count > nums.size() / 3 && a != b) {
		ret.push_back(b);
	}
	return ret;
}

int Solution::ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict) {
	unordered_set<string> set[3];
	int start = 0, mid = 1, end = 2, count = 2;
	set[start].insert(beginWord), wordDict.erase(beginWord);
	set[end].insert(endWord), wordDict.erase(endWord);
	while (set[start].size()) {
		for (auto &str : set[start]) {
			for (char &ch : *((string *)&str)) {
				char original = ch;
				for (ch = 'a'; ch <= 'z'; ++ch) {
					if (set[end].count(str)) {
						return count;
					}
					if (wordDict.count(str)) {
						set[mid].insert(str);
						wordDict.erase(str);
					}
				}
				ch = original;
			}
		}
		++count;
		if (set[mid].size() <= set[end].size()) {
			int tmp = start;
			start = mid;
			mid = tmp;
		} else {
			int tmp = end;
			end = mid;
			mid = start;
			start = tmp;
		}
		set[mid].clear();
	}
	return 0;
}

int Solution::divide(int dividend, int divisor) {
	if (divisor == 0) {
		return dividend < 0 ? INT_MIN : INT_MAX;
	}
	if (divisor == INT_MIN) {
		return dividend < 0 ? dividend == INT_MIN : 0;
	}
	unsigned int div[32], a = dividend < 0 ? -dividend : dividend, b = divisor < 0 ? -divisor : divisor, index = 0, ret = 0;
	if (a < b) return 0;
	div[0] = divisor;
	while (a >= b) {
		a -= b;
		ret += (1 << index);
		div[index++] = b;
		b <<= 1;
	}
	while ((int)a >= div[0]) {
		if (a >= div[--index]) {
			a -= div[index];
			ret += (1 << index);
		}
	}
	return (dividend ^ divisor) < 0 ? -ret : (ret > INT_MAX ? INT_MAX : ret);
}

int Solution::maximalSquare(vector<vector<char>>& matrix) {
	if (matrix.size() == 0) {
		return 0;
	}
	int maxSquare = 0, rowLen = matrix.size(), colLen = matrix[0].size();
	char *mat = &(matrix[0][0]), *pre = mat;
	for (int row = 0; row < rowLen; ++row) {
		mat = &(matrix[row][0]);
		for (int col = 0; col < colLen; ++col) {
			mat[col] -= '0';
			if (mat[col]) {
				maxSquare = 1;
			}
		}
	}
	for (int row = 1; row < rowLen; ++row) {
		mat = &(matrix[row][0]);
		for (int col = 0; col < colLen; ++col) {
			if (mat[col] && pre[col]) {
				int i, j;
				for (j = col + 1; j < colLen && pre[j] == pre[col]; ++j);
				if (j - col <= pre[col]) {
					if (j < colLen && pre[j] < pre[col]) {
						while (pre[j] == pre[j + 1]) {
							++j;
						}
						for (int i = j; i >= col && mat[i]; --i) {
							mat[i] = pre[i] + 1;
							if (mat[i] > j - col) {
								mat[i] = j - col;
							}
						}
					}
					col = j - 1;
				} else {
					for (i = col + 1; i < colLen && mat[i]; ++i);
					if (i - col > pre[col]) {
						if (maxSquare < pre[col] + 1) {
							maxSquare = pre[col] + 1;
						}
						int k = col;
						col = j - 1;
						for (; k < i; ++k) {
							if (pre[k]) {
								mat[k] = pre[k] + 1;
							} else {
								col = k;
								break;
							}
						}

					}
				}
			}
		}
		for (int i = 0; i < colLen; ++i) {
			short tmp = mat[i];
			cout << tmp;
		}
		cout << endl;
		pre = mat;
	}
	return maxSquare*maxSquare;
}

void Solution::onceSortBigHeap(vector<int> &vec, int start) {
    int &root = vec[start];
    if ((start = (start + 1) << 1) < vec.size()) {
        if (vec[start] > vec[start - 1] && vec[start] > root) {
            int tmp = vec[start];
            vec[start] = root;
            root = tmp;
            onceSortBigHeap(vec, start);
        } else if(vec[start - 1] > root) {
            int tmp = vec[start - 1];
            vec[start - 1] = root;
            root = tmp;
            onceSortBigHeap(vec, start - 1);
        }
    } else if (start - 1 < vec.size() && vec[start - 1] > root) {
        int tmp = vec[start - 1];
        vec[start - 1] = root;
        root = tmp;
    }    
}

int Solution::addDigits(int num) {
    int iRet = 0;
    iRet += num % 10;
    iRet += (num /= 10) % 10;
    iRet += (num /= 10) % 10;
    iRet += (num /= 10) % 10;
    iRet += (num /= 10) % 10;
    iRet += (num /= 10) % 10;
    iRet += (num /= 10) % 10;
    iRet += (num /= 10) % 10;
    iRet += (num /= 10) % 10;
    iRet += (num /= 10) % 10;
    iRet = (iRet % 10) + (iRet / 10) % 10;
    return (iRet % 10) + (iRet / 10) % 10;
}

void Solution::binaryTreePaths(vector<string> &vec, TreeNode* &root, vector<int> &vecPath) {
    if (root->left == NULL && root->right == NULL) {
        string str = "", s;
        for (auto &it : vecPath) {
            ss << it;
            ss >> s;
            ss.clear();
            str += s + "->";
        }
        ss << root->val;
        ss >> s;
        ss.clear();
        str += s;
        vec.push_back(str);
    } else {
        vecPath.push_back(root->val);
        if (root->left) {            
            binaryTreePaths(vec, root->left, vecPath);
        }
        if (root->right) {
            binaryTreePaths(vec, root->right, vecPath);
        }
        vecPath.pop_back();
    }
}

vector<string> Solution::binaryTreePaths(TreeNode* root) {
    vector<string> vec;
    if (root == NULL) {
        return vec;
    }
    vector<int> vecPath;
    binaryTreePaths(vec, root, vecPath);
    return vec;
}

string Solution::largestNumber(vector<int>& nums) {
    vector<string> vec; vec.reserve(nums.size());
    for (auto &it : nums) {
        vec.push_back(to_string(it));
    }
    sort(vec.begin(), vec.end(), [](const string &a, const string &b) {
        return a + b > b + a;
    });
    string strRet;
    for (auto &it : vec) {
        strRet += it;
    }
    return strRet[0] == '0' ? "0" : strRet;
}

TreeNode* Solution::buildTree(vector<int>& inorder, vector<int>& postorder, int start, int end) {
    TreeNode* root = NULL;
    if (postorder.size() > 0) {
        int tmp = postorder[postorder.size() - 1];
        postorder.pop_back();
        int i = start;
        while (i <= end && inorder[i++] != tmp);
        // must be found
        root = new TreeNode(tmp);
        root->right = buildTree(inorder, postorder, i, end);
        root->left = buildTree(inorder, postorder, start, i - 2);        
    }
    return root;
}

TreeNode* Solution::buildTree(vector<int>& inorder, vector<int>& postorder) {
    if (postorder.size() > 0 && inorder.size() == postorder.size()) {
        return buildTree(inorder, postorder, 0, inorder.size() - 1);
    }
    return NULL;
}

void Solution::nextPermutation(vector<int>& nums) {
    if (nums.size() > 0) {
        for (int i = nums.size() - 2; i >= 0; --i) {
            for (int j = nums.size() - 1; j > i; --j) {
                if (nums[j] > nums[i]) {
                    int tmp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = tmp;
                    sort(nums.begin() + i + 1, nums.end());
                    return;
                }
            }
        }
    }
    sort(nums.begin(), nums.end());
}

int Solution::forward(vector<int> &nums, int &target) {
    int begin = 0, end = nums.size() - 1, mid;
    while (begin <= end) {
        mid = (begin + end) >> 1;
        if (nums[mid] < target) {
            begin = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return nums[begin] == target ? begin : -1;
}

int Solution::backward(vector<int> &nums, int &target) {
    int begin = 0, end = nums.size() - 1, mid;
    while (begin <= end) {
        mid = (begin + end) >> 1;
        if (nums[mid] <= target) {
            begin = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return nums[end] == target ? end : -1;
}

vector<int> Solution::searchRange(vector<int>& nums, int target) {
    vector<int> ret;
    ret.push_back(forward(nums, target));
    ret.push_back(backward(nums, target));
    return ret;
}

void Solution::combine(vector<vector<int>> &result, vector<int> &helper, int &n, int k) {
    if (k == 0) {
        result.push_back(helper);
        return;
    }
    for (int start = helper.size() > 0 ? helper[helper.size() - 1] + 1 : 1; start <= n - k + 1; ++start) {
        helper.push_back(start);
        combine(result, helper, n, k - 1);
        helper.pop_back();
    }
}

vector<vector<int>> Solution::combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> helper;
    combine(result, helper, n, k);
    return result;
}

int Solution::numIslands(vector<vector<char>>& grid) {
    return 0;
}

void Solution::susetsHelper(vector<vector<int>> &result, vector<int> &helper, vector<int> &nums, int start, int k) {
    if (k == 0) {
        result.push_back(helper);
        return;
    }
    for (; start < nums.size() - k + 1; ++start) {
        helper.push_back(nums[start]);
        susetsHelper(result, helper, nums, start + 1, k - 1);
        helper.pop_back();
    }
}

vector<vector<int>> Solution::subsets(vector<int>& nums) {
    vector<vector<int>> ret;
    vector<int> helper;
    sort(nums.begin(), nums.end());
    for (int i = 0; i <= nums.size(); ++i) {
        susetsHelper(ret, helper, nums, 0, i);
    }
    return ret;
}

bool Solution::exist(vector<vector<char>>& board, string word) {
    if (word.length() == 0) {
        return true;
    }
    int pointer = 0;
    for (auto &v : board) {
        for (auto &it : v) {
            if (it == word[pointer] && ++pointer == word.length()) {
                return true;
            }
        }
    }
    return false;
}

int Solution::removeDuplicates(vector<int>& nums) {
    if (nums.size() < 1) {
        return 0;
    }
    int pre = nums[0] - 1, count = 1;
    for (auto &it : nums) {
        if (pre == it) {
            if (++count > 2) {
                it = INT_MIN;
            }
            continue;
        }
        count = 1;
        pre = it;
    }
    pre = 1;
    for (auto i = 1; i < nums.size(); ++i) {
        while (i < nums.size() && nums[i] == INT_MIN) ++i;
        if (i < nums.size()) {
            nums[pre++] = nums[i];
        }
    }
    return pre;
}

void Solution::setHelper(vector<vector<int>>& matrix, vector<int> &cols, int start, int end, int row) {
    int size = matrix[0].size(), begin = start;
    if (row >= matrix.size() || start < 0 || end >= size) {
        return;
    }
    vector<int> &v = matrix[row];
    bool bFlag = false;
    for (int i = start; i <= end; ++i) {
        if (!v[i]) {
            cols.push_back(i);
            for (int j = 0; j < matrix.size(); ++j) {
                setHelper(matrix, cols, start, i - 1, row + 1);
                start = i + 1;
            }
            bFlag = true;
        }
    }
    if (bFlag) {
        for (int i = begin; i <= end; ++i) {
            v[i] = 0;
        }
    }
    setHelper(matrix, cols, start, end, row + 1);
}
void Solution::setZeroes(vector<vector<int>>& matrix) {
    int rowEnd, colEnd, colE = 0;
    if (!(rowEnd = matrix.size()) || !(colEnd = matrix[0].size())) return;
    --rowEnd, --colEnd;
    vector<int> &rowsEnd = matrix[rowEnd];
    for (int row = rowEnd; row >= 0; --row) {
        vector<int> &rows = matrix[row];
        if (!colE && !rows[colEnd]) colE = 1;
        for (int col = colEnd - 1; col >= 0; --col) {
            if (!rows[col]) {
                rows[colEnd] = rowsEnd[col] = 0;
            }
        }
    }
    for (auto &v : matrix) {
        for (int i = 0; i < colEnd; ++i) {
            if (!v[colEnd] || !rowsEnd[i]) {
                v[i] = 0;
            }
        }
        if (colE) v[colEnd] = 0;
    }
}

double Solution::myPow(double x, int n) {
    int m = 1;
    if (n < 0) {
        n = -n;
        x = 1 / x;
    }
    bool bFlag = true;
    if (x < 0) {
        bFlag = !(n & 0x1);
        x = -x;
    }
    if (x == 1 || x == 0) {
        return x;
    }
    if (n == 0) {
        return 1;
    }
    double result = 1;
    while (result > 2.2204460492503131e-016 && m <= n) {
        if (m & n) {
            result *= x;
        }
        x *= x;
        m <<= 1;
    }
    return bFlag ? result : -result;
}

int Solution::kthSmallest1(TreeNode* root, int &k) {
    if (root == NULL) return 0;
    int left = kthSmallest(root->left, k);
    if (--k == 0) {
        return root->val;
    }
    int right = kthSmallest(root->right, k);
    return left + right;
}

void Solution::getPermutation(vector<int> &result, int &start, int &n, int &k, int &count) {
    if (n > 1) {
        std::swap(*(result.begin() + start), *(result.begin() + start + (k - 1) / count));
        sort(result.begin() + start, result.begin() + ++start + (k - 1) / count);
        k -= (k - 1) / count * count;
        count /= --n;
        getPermutation(result, start, n, k, count);
    }
}
string Solution::getPermutation(int n, int k) {
    int count = 1, start = 0;
    vector<int> helper;
    for (int i = 1; i < n; ++i) {
        count *= i;
        helper.push_back(i);
    }
    helper.push_back(n);
    getPermutation(helper, start, n, k, count);
    string result;
    for (auto &it : helper) {
        result += to_string(it);
    }
    return result;
}

bool Solution::lispExpression(string &str, int &start, int &result) {
	while (start < str.length() && str[start] == ' ') {
		++start;
	}
	if (start < str.length()) {
		if (str[start] == '(') {
            long ret = 0;
            while (++start < str.length() && str[start] == ' ');
            if (start < str.length() && str[start] == '+') {
                while (++start < str.length() && str[start] == ' ');
                while (start < str.length() && str[start] != ')') {
                    if (str[start] == '(') {
                        int tmp;
                        if (lispExpression(str, start, tmp)) {
                            ret += tmp;
                        } else {
                            return false;
                        }
                    } else if (str[start] <= '9' && str[start] >= '0') {
                        int tmp = 0;
                        while (start < str.length() && str[start] <= '9' && str[start] >= '0') {
                            tmp = tmp * 10 + str[start] - '0';
                            ++start;
                        }
                        ret += tmp;
                    } else {
                        return false;
                    }
                    while (start < str.length() && str[start] == ' ') ++start;
                }             
            } else if (start < str.length() && str[start] == '-') {
                while (++start < str.length() && str[start] == ' ');
                int count = 0;
                while (start < str.length() && str[start] != ')') {
                    int tmp = 0;
                    if (str[start] == '(') {
                        if (!lispExpression(str, start, tmp)) {
                            return false;
                        }
                    } else if (str[start] <= '9' && str[start] >= '0') {
                        while (start < str.length() && str[start] <= '9' && str[start] >= '0') {
                            tmp = tmp * 10 + str[start] - '0';
                            ++start;
                        }
                    } else {
                        return false;
                    }
                    while (start < str.length() && str[start] == ' ') ++start;
                    if (++count >= 2) {
                        ret = -ret - tmp;
                        break;
                    } else {
                        ret = -tmp;
                    }
                }
            } else if (start < str.length() && str[start] == '*') {
                while (++start < str.length() && str[start] == ' ');
                int count = 0;
                ret = 1;
                while (start < str.length() && str[start] != ')') {
                    int tmp = 0;
                    if (str[start] == '(') {
                        if (!lispExpression(str, start, tmp)) {
                            return false;
                        }
                    } else if (str[start] <= '9' && str[start] >= '0') {
                        while (start < str.length() && str[start] <= '9' && str[start] >= '0') {
                            tmp = tmp * 10 + str[start] - '0';
                            ++start;
                        }
                    } else {
                        return false;
                    }
                    while (start < str.length() && str[start] == ' ') ++start;
                    ret *= tmp;
                    ++count;
                }
                if (count < 2) {
                    return false;
                }
            } else {
                return false;
            }
            if (start < str.length() && str[start] == ')') {
                ++start;
                result = ret;
                return true;
            } else {
                ++start;
                return false;
            }
		} else {
            return false;
		}
	}
}

int Solution::totalNQueensHelper(int &n, int &count, vector<int> &helper) {
    if (count == n) {
        return 1;
    }
    int result = 0;
    for (int i = 0; i < n; ++i) {
        int cur = i, left = count - i + (n << 1), right = count + i + (n << 2);
        if (!helper[i] && !helper[left] && !helper[right]) {
            helper[i] = helper[left] = helper[right] = 1;
            result += totalNQueensHelper(n, ++count, helper);;
            --count;
            helper[i] = helper[left] = helper[right] = 0;
        }
    }
    return result;
}

int Solution::totalNQueens(int n) {
    vector<int> helper(n * 6, 0);
    int count = 0;
    return totalNQueensHelper(n, count, helper);
}

int Solution::findMin1(vector<int>& nums) {
    int start = 0, end = nums.size() - 1, mid;
    while (start < end) {
        mid = (start + end) >> 1;
        if (nums[mid] < nums[start]) {
            end = mid;
        } else {
            if (nums[start] < nums[end]) {
                end = mid;
            } else if (nums[start] == nums[end]) {
                ++start;
            } else {
                start = mid + 1;
            }
        }
    }
    return nums[start];
}
double Solution::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    vector<int> &numsSmall = nums1.size() < nums2.size() ? nums1 : nums2;
    vector<int> &numsLarge = nums1.size() >= nums2.size() ? nums1 : nums2;
    int size1 = numsSmall.size(), size2 = numsLarge.size();
    if (size1 <= 0) {
        return (double)(numsLarge[(size2 - 1) >> 1] + numsLarge[size2 >> 1]) / 2.0;
    }
    int low = 0, high = size1 << 1, midSmall, midLarge;
    while (low <= high) {
        midSmall = (low + high) >> 1;
        midLarge = size1 + size2 - midSmall;
        int L1 = midSmall == 0 ? INT_MIN : numsSmall[(midSmall - 1) >> 1];
        int R1 = midSmall == (size1 << 1) ? INT_MAX : numsSmall[midSmall >> 1];
        int L2 = midLarge == 0 ? INT_MIN : numsLarge[(midLarge - 1) >> 1];
        int R2 = midLarge == (size2 << 1) ? INT_MAX : numsLarge[midLarge >> 1];
        if (L1 > R2) {
            high = midSmall - 1;
        } else if (L2 > R1) {
            low = midSmall + 1;
        } else {
            return (double)(max(L1, L2) + min(R1, R2)) / 2.0;
        }
    }
    return -1;
}

int Solution::hIndex(vector<int>& citations) {
	sort(citations.begin(), citations.end(), [](int a, int b) {
		return a < b;
	});
	int start = 0, last = citations.size(), end = last, mid;
	while (start < end) {
		mid = (start + end) / 2;
		if (citations[mid] < last - mid) {
			start = mid + 1;
		} else {
			end = mid;
		}
	}
	return last - start;
	//return citations[start] == last - start ? last - start : last - start + 1;
/*
	sort(citations.begin(), citations.end(), [](int a, int b) {
		return a > b;
	});
	int result;
	for (result = 0; result < citations.size() && citations[result] > result; ++result);
	return result;
*/

/*
	int size = citations.size();
	vector<int> temp(citations.size() + 1);
	for (auto &it : citations) {
		++temp[it < size ? it : size];
	}
	int result = size, h = 0;
	for (; result && (h += temp[result]) < result; --result);
	return result <= 0 ? h : result;
*/
}

vector<Interval> Solution::insert(vector<Interval>& intervals, Interval newInterval) {
	vector<Interval> result;
	if (intervals.size() <= 0) {
		result.push_back(newInterval);
		return result;
	}
	int start = 0, end = intervals.size(), mid;
	while (start < end) {
		mid = (start + end) >> 1;
		if (intervals[mid].end < newInterval.start) {
			start = mid + 1;
		} else {
			end = mid;
		}
	}
	for (int i = 0; i < start; ++i) {
		result.push_back(intervals[i]);
	}
	if (start >= intervals.size()) {
		result.push_back(newInterval);
		return result;
	}
	if (intervals[start].start <= newInterval.start && intervals[start].end >= newInterval.start) {
		result.push_back(intervals[start]);
		result[start].start = result[start].start < newInterval.start ? result[start].start : newInterval.start;
		result[start].end = result[start].end < newInterval.end ? newInterval.end : result[start].end;
		++start;
	} else {
		result.push_back(newInterval);
	}
	for (int i = start; i < intervals.size(); ++i) {
		if (result[result.size() - 1].end >= intervals[i].start) {
			result[result.size() - 1].end = result[result.size() - 1].end >= intervals[i].end ? result[result.size() - 1].end : intervals[i].end;
		} else {
			result.push_back(intervals[i]);
		}
	}
	return result;
}

string Solution::numberToWords(int num) {
	const static string base[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", 
	"Seventeen", "Eighteen", "Nineteen"};
	const static string Tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
	string result = "";
	if (num / 1000000000) {
		result += numberToWords(num / 1000000000) + " " + "Billion";
		string tmp = numberToWords(num % 1000000000);
		if (tmp != "Zero") {
			result += " " + tmp;
		}
	} else if (num / 1000000) {
		result += numberToWords(num / 1000000) + " " + "Million";
		string tmp = numberToWords(num % 1000000);
		if (tmp != "Zero") {
			result += " " + tmp;
		}
	} else if (num / 1000) {
		result += numberToWords(num / 1000) + " " + "Thousand";
		string tmp = numberToWords(num % 1000);
		if (tmp != "Zero") {
			result += " " + tmp;
		}
	} else if (num / 100) {
		result += numberToWords(num / 100) + " " + "Hundred";
		string tmp = numberToWords(num % 100);
		if (tmp != "Zero") {
			result += " " + tmp;
		}
	} else if (Tens[num / 10] == "") {
		if (base[num] == "Zero") {
			if (result == "") {
				result = base[num];
			}
		} else {
			result =  result == "" ? base[num] : result + " " + base[num];
		}
	} else {
		result = result == "" ? Tens[num / 10] + (base[num % 10] == "Zero" ? "" : " " + base[num % 10]) : " " + Tens[num / 10] + " " + (base[num % 10] == "Zero" ? "" : " " + base[num % 10]);
	}
	return result;
}

int Solution::trap(vector<int>& height) {
    if (height.empty()) return 0;
    auto left = height.begin(), right = height.end() - 1;
    int level = 0, water = 0;
    while (left != right + 1) {
        int lower = *left < *right ? *left++ : *right--;
        level = max(level, lower);
        water += level - lower;
    }
    return water;
}
