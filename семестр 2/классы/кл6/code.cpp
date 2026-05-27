#include <iostream>
#include <string>

using namespace std;

#include "list.h"

int main() {
	List<int> listI = { 1, 2, 3, 4 };

	for (auto it = list.rbegin(); it != list.rend(); it++) {
		cout << *it << " ";
	}
}