#include <iostream>
using namespace std;

void show(int arr[100][100], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}


int main() {
	srand(time(0));
	int N = 4;
	int arr[100][100];
	int answarr[100];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j] = ((double)rand() / RAND_MAX) * (10-1)+1;
			answarr[i] = 1;
		}
	}
	show(arr, N);

	int dmx = arr[0][0]; 
	for (int i = 0; i < N; i++) { // вычисление максимального элемента на диагоналях
		if (arr[i][i] > dmx) dmx = arr[i][i];
		if (arr[i][N-i-1] > dmx) dmx = arr[i][N-i-1];
	}

	for (int i = 0; i < N; i++) {
		if (arr[0][i] > dmx) {
			for (int j = 0; j < N; j++) {
				answarr[j] *= arr[j][i];
			}
		}
	}
	cout << dmx << endl << endl;

	for (int j = 0; j < N; j++) {
		cout << answarr[j] << endl;
	}

}