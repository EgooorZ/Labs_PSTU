#include <iostream>
using namespace std;


void move(int tower[][3], int N, int start, int point) {
	static int step = 0;
	cout << " step: " << step << " | " << start << " => " << point << endl << endl;
	step++;
	int tmp = 0;
	for (int i = 0; i < N; i++) {
		if (tower[i][start] != 0) {
			tmp = tower[i][start];
			tower[i][start] = 0;
			break;
		}
	}
	for (int i = 0; i < N + 1; i++) {
		if (i < N) {
			if (tower[i][point] != 0) {
				tower[i - 1][point] = tmp;
				break;
			}
		}
		else {
			tower[N-1][point] = tmp;
		}


	}

}
void visualization(int tower[][3], int N) {
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < (N * 2 + 1) / 2; k++) {
			cout << " ";
		}
		cout << "|";
		for (int k = 0; k < (N * 2 + 1) / 2; k++) {
			cout << " ";
		}
		cout << "\t";
	}

	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {

			for (int k = 0; k < (N * 2 + 1) / 2 - tower[i][j] / 2; k++) {
				cout << " ";
			}
			if (tower[i][j] == 0) {
				cout << "|";
			}
			else {
				for (int k = 0; k < tower[i][j]; k++) {
					cout << "*";
				}
			}
			for (int k = 0; k < (N * 2 + 1) / 2 - tower[i][j] / 2; k++) {
				cout << " ";
			}
			cout << "\t";
		}
		cout << endl;
	}
	for (int j = 0; j < 3; j++) {
		for (int p = 0; p < (N * 2 + 1); p++) {
			cout << "=";
		}
		cout << "\t";
	}
	cout << endl;
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < (N * 2 + 1) / 2; k++) {
			cout << " ";
		}
		cout << j;
		for (int k = 0; k < (N * 2 + 1) / 2; k++) {
			cout << " ";
		}
		cout << "\t";
	}
	cout << endl << endl << endl;


	/*
			 |
			***
		   *****
		  *******
		 *********
		 =========
	*/
}

// n - количество колец
// start - столбец начала
// point - цель куда ложим
// temp - вспомогательный столб
void HANOI(int tower[][3], int n, int N, int start, int point, int temp) {
	if (n <= 0) return;
	HANOI(tower, n - 1, N, start, temp, point);
	
	move(tower, N, start, point);
	visualization(tower, N);
	// cout << start << " => " << point << endl;
	HANOI(tower, n - 1, N, temp, point, start);
}


int main() {
	const int N = 3;
	
	int tower[N][3];
	cout << " start position" << endl << endl;
	for (int i = 0; i < N; i++) {
		tower[i][0] = 2 * (i + 1) + 1;
		tower[i][1] = 0;
		tower[i][2] = 0;
	}
	visualization(tower, N);
	HANOI(tower, N, N, 0, 2, 1);
}