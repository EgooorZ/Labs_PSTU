#include <iostream>
using namespace std;

int FIBONACCI(int n) {
	if (n <= 1) return 0;
	else if (n == 2) return 1;
	return FIBONACCI(n - 2) + FIBONACCI(n - 1);
}

int main() {
	for (size_t i = 1; i < 20; i++) {
		cout << FIBONACCI(i) << " ";
	}
}