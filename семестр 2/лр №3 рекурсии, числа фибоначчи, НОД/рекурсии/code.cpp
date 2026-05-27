#include <iostream>
#include <iomanip>

using namespace std;

double pi = 3.141592653589793;
float E = 0.0001;

float Func(float x) {
	return 1/4.0 * (x*x - pi*pi/3);
}
float FuncN(float x, int n) {
	return pow(-1, n) * cos(n * x) / (n * n);
}

float FuncSumEps(int x, int n) {
	if (abs(FuncN(x, n)) > E)
		return FuncN(x, n) + FuncSumEps(x, n + 1);
	return 0;
}
float FuncSumN(float x, int n) {
	if (n > 0) return FuncN(x, n) + FuncSumN(x, n - 1);
	return 0;
}



int main() {
	float a = pi / 5;
	float b = pi;
	int k = 10;


	cout << "|\t    x\t\t|\t FuncSumN\t|\tFuncSumEps\t|\t     y\t\t|" << endl;
	for (int i = 0; i < 97; i++) {
		cout << "-";
	}
	cout << endl;
	for (float x = a; x <= b; x += (b-a)/k) {
		cout << fixed << setprecision(7) << "|\t" << x << " \t|\t";
		cout << fixed << setprecision(7) << FuncSumN(x, 20) << "\t|\t";
		cout << fixed << setprecision(7) << FuncSumEps(x, 1) << "\t|\t";

		cout << fixed << setprecision(7) << Func(x) << "\t|" << endl;
	}


	return 0;
}