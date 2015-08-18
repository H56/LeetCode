#include "GlobalFunction.h"

int getVersionNum(char *str, int *digits) {
	if (*str == '\0') {
		*digits = 0;
		return 0;
	}
	if (*str == '.')
		str++;
	int count = 0;
	while (1) {
		if (str[count] >= '0' && str[count] <= '9') count++;
		else break;
	}
	// 	char tmp[count+1];
	char *tmp = new char[count + 1];
	strncpy(tmp, str, count);
	tmp[count] = '\0';
	*digits = count;
	int iRet = atoi(tmp);
	delete[] tmp;
	return iRet;
}

int compareVersion(char *version1, char *version2) {
	int count1, count2;
	while (1) {
		if (getVersionNum(version1, &count1) > getVersionNum(version2, &count2))
			return 1;
		if (getVersionNum(version1, &count1) < getVersionNum(version2, &count2))
			return -1;
		version1 += count1;
		version2 += count2;
		if (*version1 == '\0' && *version2 == '\0')
			return 0;
	}
}

int mySqrt(int x) {
	int a = 0, shift = 15, b = 0x8000, temp;
	if (x <= 1) {
		return x;
	}
	do {
		temp = ((a << 1) + b) << (shift--);
		if (temp <= x) {
			a += b;
			x -= temp;
		}
	} while (b >>= 1);
	return a;
}
