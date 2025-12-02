#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n, i, p;
    cin >> n;
    p = 1;
    if (n <= 0)
    {
        cout << "Невозможно посчитать произведение N перых натуральных чисел";
    }
    else
    {
        for (i = 1; i <= n; i++)
        {
            p = p * i;
        }

        cout << "Произведение N перых натуральных чисел: " << p;
    }
    return(0);
}

