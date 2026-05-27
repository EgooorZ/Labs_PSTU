#include <iostream>
#include <cmath>

using namespace std;

double myLog(int n) {
    return log(n);
}
double myLog(double n) {
    return log10(n);
}

int main() {
    cout << myLog(10) << " ";
    cout << myLog(10.0);
}