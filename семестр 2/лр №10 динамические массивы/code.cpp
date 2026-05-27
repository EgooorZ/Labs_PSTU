#include <iostream>

using namespace std;

int main() {
	srand(time(0));
	int rows = 3, cols = 4;

	int** arr = new int*[rows];
	for (int i = 0; i < rows; i++) {
		arr[i] = new int[cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			arr[i][j] = ((float)rand() / RAND_MAX) * 10;
		}
	}

	int mn = arr[0][0];
	int mni = 0;
	int mnj = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << "\t" << arr[i][j];
			if (arr[i][j] < mn) { 
				mn = arr[i][j]; 
				mni = i;
				mnj = j;
			}
		}
		cout << endl;
	}
	cout << endl << endl;
	
	int** tmp = new int* [rows-1];
	for (int i = 0; i < rows-1; i++) {
		tmp[i] = new int[cols-1];
	}
	
	for (int i = 0, ti = 0; i < rows; i++) {
		if (i == mni) {
			for (int j = 0; j < cols; j++) {
				cout << "\t-";
			}
			cout << endl;
			continue;
		}

		cout << "\t";
		for (int j = 0, tj = 0; j < cols; j++) {
			if (j == mnj) {
				cout << "-\t";
			}
			else {
				cout << arr[i][j] << "\t";
				tmp[ti][tj] = arr[i][j];
				tj++;
			}
		}
		cout << endl;
		ti++;
	}
	cout << endl << endl;


	for (int i = 0; i < rows-1; i++) { delete[] tmp[i]; }
	for (int i = 0; i < rows; i++) { delete[] arr[i]; }
	delete[] tmp;
	delete[] arr;
}