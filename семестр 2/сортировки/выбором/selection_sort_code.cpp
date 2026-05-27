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

	int N = 8;
	int arr[100];
	int K = 2;

	for (int i = 0; i < N; i++) {
		arr[i] = ((float)rand() / RAND_MAX) * 100;
	}
	show(arr, N);

	int tmp;
	int mn;
	int mni;
	for (int i = 0; i < N; i++) {
		mn = arr[i];
		mni = i;
		for (int j = i + 1; j < N; j++) {
			if (mn > arr[j]) {
				mn = arr[j];
				mni = j;
			}
		}
		tmp = arr[i];
		arr[i] = mn;
		arr[mni] = tmp;
		show(arr, N);
	}

	cout << endl;
	show(arr, N);
}
