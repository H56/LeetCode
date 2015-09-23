#include <iostream>
#include "Solution.h"
using namespace std;

int main(void) {
	int n;
    Solution so;
    string str1, str2;
    while (cin >> str1 >> str2) {
        cout << boolalpha << so.isScramble(str1, str2) << endl;
    }
    system("pause");
	return 0;
}
