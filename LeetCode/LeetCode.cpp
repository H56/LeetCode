#include <iostream>
#include "Solution.h"
using namespace std;
bool isScrambleRecur(string &s1, string &s2)
{
	string s1cop = s1, s2cop = s2;
	sort(s1cop.begin(), s1cop.end());
	sort(s2cop.begin(), s2cop.end());
	if(s1cop != s2cop)return false;//两个字符串所含字母不同
	if(s1 == s2)return true;

	size_t len = s1.size();
	for(int i = 1; i < len; i++)//分割位置
	{
		string s1left = s1.substr(0, i);
		string s1right = s1.substr(i);
		string s2left = s2.substr(0, i);
		string s2right = s2.substr(i);
		if(isScrambleRecur(s1left, s2left) && isScrambleRecur(s1right, s2right))
			return true;
		s2left = s2.substr(0, len-i);
		s2right = s2.substr(len-i);
		if(isScrambleRecur(s1left, s2right) && isScrambleRecur(s1right, s2left))
			return true;
	}
	return false;
}
bool isScramble(string s1, string s2) {
	return isScrambleRecur(s1,s2);
}
int main(void) {
	int n;
    Solution so;
    //string str1, str2;
    //while (cin >> str1 >> str2) {
    //    cout << boolalpha << isScramble(str1, str2) << endl;
    //}
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(2);
	cout << so.findDuplicate(nums) << endl;

    system("pause");
	return 0;
}
