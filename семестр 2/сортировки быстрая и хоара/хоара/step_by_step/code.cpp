#include <iostream>
using namespace std;


void draw(int arr[], int size, int pivot, int i, int j) {
	int max = arr[0];

	for (int i = 1; i < size; i++) { if (arr[i] > max) { max = arr[i]; } }

	for (int i = max; i >= 0; i--) {
		cout << " ";
		for (int j = 0; j < size; j++) {

			if (arr[j] > i) {
				if (i == pivot) cout << "[_]_";
				else cout << "[ ] ";
			}
			else {
				if (i == pivot) cout << "____";
				else cout << "    ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < size; i++) {
		cout << "  " << arr[i] << " ";
	}
	cout << endl;

	for (int s = 0; s < i; s++) { cout << "    "; } cout << "  i" << endl;
	for (int s = 0; s < j; s++) { cout << "    "; } cout << "  j" << endl << endl;
	cout << "pivot под номером: " << pivot << " со значением " << arr[pivot] << endl << endl;
}

int swap2(int& a1, int& a2) {
	static int count = 0;
	int a = a1;
	a1 = a2;
	a2 = a;

	return ++count;
}




int partitionHoare(int arr[], int low, int high, int size) {
	// часто берут центральный или первый элемент

	int pI = (high + low) / 2;
	int pivot = arr[pI];
	int i = low - 1; // левый индекс на 1 меньше левой границы
	int j = high + 1; // правый индекс на 1 больше правой границы

	while (true)
	{
		do {
			i++;
			draw(arr, size, pivot, i, j);
			cout << "    i   P" << endl;
			if (arr[i] >= pivot) cout << " i: " << arr[i] << " >= " << pivot << "  значит фиксируем i и переходимк j" << endl << endl << endl << endl;
			else cout << " i: " << arr[i] << " < " << pivot << "  значит двигаем i вправо" << endl << endl << endl << endl;
		} while (arr[i] < pivot);

		do {
			j--;
			draw(arr, size, pivot, i, j);

			cout << "    j   P" << endl;
			if (arr[j] > pivot) cout << " j: " << arr[j] << " > " << pivot << "  значит двигаем j влево" << endl << endl << endl << endl;
			else cout << " j: " << arr[j] << " > " << pivot << " значит менем j с i" << endl << endl << endl << endl;

		} while (arr[j] > pivot);

		if (i >= j) {
			cout << " i >= j выходим" << endl;
			return j;
		}

		if (pI == j) pI = i;
		else if (pI == i) pI = j;

		swap2(arr[i], arr[j]);
	}
}

void quickSortHoare(int arr[], int low, int high, int size) {
	if (low < high) {
		int pI = partitionHoare(arr, low, high, size);

		quickSortHoare(arr, low, pI, size);
		quickSortHoare(arr, pI + 1, high, size);
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	int size = 10;

	int arr[10] = { 1, 7, 1, 9, 5, 3, 5, 4, 8, 5 };

	quickSortHoare(arr, 0, 9, 10);

	cout << endl << endl << " количество перестановок: " << swap2(arr[0], arr[0]) - 1;
}