#include <iostream>
using namespace std;

// n - количество колец
// start - столбец начала
// point - цель куда кладем
// temp - вспомогательный столб
void HANOI(int n, int start, int point, int temp) {
	if (n <= 0) return;
	HANOI(n - 1, start, temp, point);
	cout << start << " => " << point << endl;
	HANOI(n - 1, temp, point, start);
}

int main() {
	HANOI(3, 1, 3, 2);
}