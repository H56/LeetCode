#include <iostream>
#include "Solution.h"
using namespace std;

int main(void) {
	int n;
    Solution so;
    vector<int> height = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    cout << so.trap(height) << endl;
    system("pause");
	return 0;
}
