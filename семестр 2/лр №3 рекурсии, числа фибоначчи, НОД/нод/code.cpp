#include <iostream>
using namespace std;

int NOD(int n, int m) {
	if (n == m) return n;
	if (n > m) return NOD(n - m, m);
	return NOD(n, m - n);
}

int main() {
	cout << " NOD(10, 3)"  << "\t" << NOD(10, 3) 	<< endl;
	cout << " NOD(40, 12)" << "\t" << NOD(40, 12)	<< endl;
	cout << " NOD(13, 13)" << "\t" << NOD(13, 13)	<< endl;
	cout << " NOD(5, 25)"  << "\t" << NOD(5, 25)	<< endl;
}