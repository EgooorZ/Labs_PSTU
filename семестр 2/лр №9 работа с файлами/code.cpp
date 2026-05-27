#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

bool isHaveA(string str) {
	for (char c : str) {
		if ((c == 'À') || (c == 'A') || (c == 'à') || (c == 'a')) return 1;
	}
	return 0;
}

int countingVowels(string str) {
	static string vowelLetters = "ÀÎÓÛÝß¨ÞÅÈàîóûýÿ¸þåèAEIOUaeiou";

	int count = 0;
	for (char c : str) {
		for (char l : vowelLetters) {
			if (l == c) {
				count++;
				break;
			}
		}
	}
	return count;



}

int main() {
	// SetConsoleCP(1251);
	// SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");


	fstream file("F1.txt");
	string str, buff = "";
	int N1, N2;
	int vi = 0, vmx, vc;

	N1 = 5;
	N2 = 20;

	for (int i = 0; getline(file, str); i++) {
		vc = countingVowels(str);
		if (i == 0) {
			vi = 0;
			vmx = vc;
		}
		else if (vc > vmx) {
			vi = i;
			vmx = vc;
		}

		if ((i > N1) && (i < N2)) {
			if (!isHaveA(str)) {
				buff += str + "\n";
			}
		}
	}
	file.close();

	file.open("F2.txt");
	file << buff;

	cout << " " << vi;
}