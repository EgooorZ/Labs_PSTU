#include <iostream>

using namespace std;

void show(int arr[100], int N) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	srand(time(0));

	int N = 5;
	int arr[100];
	int K = 2;

	for (int i = 0; i < N; i++) {
		arr[i] = ((float)rand() / RAND_MAX) * 100;
	}
	show(arr, N);


	int si = 0;
	int tmp;
	for (int i = si + 1; i < N; i++) {

		for (int k = i, l = 0; k >= 0; k--, l++) {
			if (arr[k] < arr[si - l]) {
				tmp = arr[k];
				arr[k] = arr[si - l];
				arr[si - l] = tmp;

				show(arr, N);
			}
			else {
				// cout << endl;
				break;
			}
		}
		si++;

	}
	cout << endl;
	show(arr, N);
	return 0;
}