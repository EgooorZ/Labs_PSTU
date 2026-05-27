#include <iostream>
#include <string>
#include <cstdarg>

using namespace std;

int two2ten(string s) {
	int n10 = 0;
	int n2 = 0;

	for (int i = 0; i < s.length(); i++) {
		n2 = s[i] - '0';
		// cout << s[i] << " " << n2 * pow(2, s.length()-i-1) << endl;
		n10 += n2 * pow(2, s.length() - i-1);
	}

	return n10;
}
string ten2three(int n10) {
	string n3 = "";

	while (n10 > 0) {
		n3 = to_string(n10 % 3) + n3;
		n10 /= 3;
	}

	return n3;
}


void two2three(int count, ...) {
	va_list args; 
	va_start(args, count); 
	string n;

	for (int i = 0; i < count; i++) {
		n = va_arg(args, const char*);
		cout << ten2three(two2ten(n)) << " ";
	}
	cout << endl;
	va_end(args);
}

int main() {
	two2three(3, "11101", "10101", "11001");
	two2three(6, "11101", "10101", "11001", "111001", "101", "10101001");
	two2three(7, "11101", "10101", "11001", "111001", "101", "10101001", "110");
}