#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n;
    cin >> n;
    if (n <= 0)
    {
        cout << "Невозможно посчитать сумму N первых натуральных чисел";
    }
    else
    {
        cout << "Сумма N первых натуральных чисел: " << (n * (n + 1)) / 2;
    }
    return(0);
}

