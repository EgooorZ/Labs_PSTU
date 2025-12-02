#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n, i, k, r;
    cout << "Введите количество элементов последовательности: ";
    cin >> n;
    k = 0;
    i = 0;

    while (k == 0 && i < n)
    {
        cin >> k;
        i = i + 1;
    }

    if (k != 0 && i < n)
    {
        r = k;

        for (; i < n; i++)
        {
            cin >> k;
        }

        if (r > 0)
        {
            cout << "Раньше вводится положительное число";
        }
        else
        {
            cout << "Раньше вводится отрицательное число";
        }
        
    }
    else
    {
        cout << "Вся последовательность - нули";
    }
    
    return(0);
}
