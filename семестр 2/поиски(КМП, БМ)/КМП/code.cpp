#include <iostream>
#include <string>

using namespace std;


/*
	a b c a b c e a b c a b c d
	| | | | | | /
	a b c a b c<d

	не совпало d => ищем элемент под индексом 3 (от буквы с которая стоит до d)
	| 0 1 2(3)4 5 6 |
	| a b c a b c d |
	| 0 0 0 1 2(3)0 |
	под индексом 3 стоит а, сдвигаю чтобы под е стояла эта а

	a b c a b c e a b c a b c d
		  | | | /
		  a b c<a b c d

	не совпало a => ищем элемент под индексом 0 (у c до а)
	|(0)1 2 3 4 5 6 |
	| a b c a b c d |
	| 0 0(0)1 2 3 0 |
	под индексом 0 стоит а, сдвигаем чтобы под е стояла эта а

	a b c a b c e a b c a b c d
				/
			   <a b c a b c d

	т.к. элемент последний, просто сдвигаем все на 1
	a b c a b c e a b c a b c d
				  | | | | | | |
				  a b c a b c d - совпадение

*/


struct Shift {
	char letter;
	int shift = 0;
};

string createPrefix(string s, int len) {
	string prefix = "";
	for (int i = 0; i < len; i++) {
		prefix += s[i];
	}
	return prefix;
}
string createSuffix(string s, int len, int start) {
	string suffix = "";

	for (int st = start, i = 0; i < len; st--, i++) {
		suffix = s[st] + suffix;
	}
	return suffix;
}

// Алгоритм Кнута-Морриса-Пратта
int KMPSearch(string str, string substr) {
	int size = substr.size();
	string prefix;
	string suffix;

	Shift* tsh = new Shift[size];
	int idx;

	for (int i = 0; i < size; i++) {
		idx = 0;
		for (int j = 1; j < i+1; j++) {
			prefix = createPrefix(substr, j);
			suffix = createSuffix(substr, j, i);
			// cout << prefix << " " << suffix << endl;

			if (prefix == suffix) {
				idx = j;
				break;
			}
		}
		tsh[i].shift  = idx;
		tsh[i].letter = substr[i];
		// cout << idx << " " << substr[i] << endl << endl;
	}
	// cout << " таблица сдвигов" << endl << "  ";
	// for (int i = 0; i < size; i++) { cout  << tsh[i].shift << " "; }
	// cout << endl;

	bool f;
	for (int i = 0; i < size; i++) {
		f = 1;
		// cout << str << endl;
		// for (int i = 0; i < idx; i++) cout << "_";

		for (int j = 0; j < size; j++) {
			// cout << substr[j];

			if (substr[j] != str[j+idx]) {
				f = 0;
				if (j > 0) idx += abs(tsh[j-1].shift - j);
				else idx++;
				// cout << " - !   " << substr[j] << " != " << str[j + idx] << " idx = " << idx << endl << endl;
				break;
			}
		}
		if (f) {
			delete[] tsh;
			return idx;
		}
	}

	delete[] tsh;
	return -1;
}



int main() {
	setlocale(LC_ALL, "ru");
	
	string str = "abcabceabcabcd";
	string substr = "abcabcd";

	cout << " " << KMPSearch(str, substr);
}