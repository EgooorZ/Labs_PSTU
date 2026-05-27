#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

string sort(string arr) {
	int n = arr.length();
	char b;

	for (int j = 0; j < n - 1; j++) {
		for (int i = 0; i < n - j - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				b = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = b;
			}
		}
	}

	return arr;
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string str;
	getline(cin, str);

	int countSpace = 1;
	for (auto s : str) if (s == ' ') countSpace++;
	string* splitStr = new string[countSpace];

	for (int i = 0, c = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			c++;
			// cout << endl;
		}
		else if (((str[i] - '0') >= 0) && ((str[i] - '0') <= 9)) {
			splitStr[c] += str[i];
			// cout << splitStr[c] << " ";
		}
	}

	for (int i = 0; i < countSpace; i++) {
		splitStr[i] = sort(splitStr[i]);
		// cout << splitStr[i] << " ";
	}


	for (int i = 0, c = 0, j = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			c++;
			j = 0;
		}
		else if (((str[i] - '0') >= 0) && ((str[i] - '0') <= 9)) {
			str[i] = splitStr[c][j];
			j++;
		}

	}

	cout << str;

	delete[] splitStr;
}