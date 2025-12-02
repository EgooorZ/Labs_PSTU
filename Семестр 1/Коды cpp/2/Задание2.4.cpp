#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n, i, j;

    cin >> n;

    if (n > 3 && n % 2 == 1)
    {
        cout << "*" << endl;

        for (i = 0; i < n - 2; i++)
        {
            cout << "*";
            for (j = 0; j < i; j++)
            {
                cout << " ";
            }
            cout << "*" << endl;
        }

        for (i = 0;i<n;i++)
        {
            cout << "*";
        }
    }
    else
    {
        cout << "Введено число не по условию ";
    }
    return(0);
}

