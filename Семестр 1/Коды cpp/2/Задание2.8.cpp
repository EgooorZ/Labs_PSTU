#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n, i, j;
    cout << "Введите длину катетов треугольника (больше 2): ";
    cin >> n;
    if (n > 2)
    {

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < i + 1; j++)
            {
                cout << "*";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Длина должна быть >2";
    }
    return(0);
}
