#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int a, b, c, D;
    float x1, x2;
    cout << "Введите коэффициенты уравнения: ";
    cin >> a;
    cin >> b;
    cin >> c;
    D = pow(b, 2) - 4 * a * c;

    if (D > 0)
    {
        x1 = ((-b) + sqrt(D)) / (2 * a);
        x2 = ((-b) - sqrt(D)) / (2 * a);
        cout << "Корни уравнения: " << x1 << ", " << x2;
    }
    else if (D == 0)
    {
        x1 = (-b) / (2 * a);
        cout << "Корень уравнения: " << x1;
    }
    else
    {
        cout << "Корней нет";
    }

    return(0);
}