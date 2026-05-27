#include <iostream>
using namespace std;

int main() {
	srand(time(0));
	const int size = 10;
	float tmp;

	int arr[size];

	int range_min = 0;
	int range_max = 50;

	for (int i = 0; i < size; i++) {
		arr[i] = ((float)rand() / RAND_MAX) * (range_max - range_min) + range_min;
		cout << arr[i] << " ";
	}
	cout << endl;

	for (int j = 0; j < size - 1; j++) {
		for (int i = 0; i < size - j - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}
	cout << endl;

	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}