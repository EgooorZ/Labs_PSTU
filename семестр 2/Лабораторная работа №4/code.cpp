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

	int N = 14;
	int arr[100];


	for (int i = 0; i < N; i++) {
		arr[i] = ((float)rand() / RAND_MAX) * 100;
	}
	show(arr, N);

	 
	if (N%2 != 0) {
		for (int i = N/2; i < N; i++) {
			arr[i] = arr[i + 1]; 
		}
		N--;
	}


	int tmp;
	for (int i = 0; i < N/2; i++) {
		tmp = arr[i];
		arr[i] = arr[N-1-i];
		arr[N-1-i] = tmp;
	}
	show(arr, N);


	for (int i = N; i >= 0; i--) {
		arr[i + 3] = arr[i];
	}
	N += 3;
	for (int I = 0; I < 3; I++) {
		arr[I] = arr[I + 10+3] - 2;
	}
	show(arr, N);

}