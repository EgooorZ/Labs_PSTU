#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n, i, j;
    cin >> n;
    
    cout << "N звездочек" << endl;
    for (i = 0 ;i < sqrt(n); i++)
    {
        for (j = 0; j < sqrt(n); j++)
        {
            cout << "* ";
        }
        cout << endl;
    }

    cout << endl << "Заполненный квадрат со стороной N" << endl;
    for (i = 0 ; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << "* ";
        }
        cout << endl;
    }


    cout << endl << "Пустой квадрат со стороной N" << endl;
    for (i = 0; i < n; i++)
    {
        cout << "* ";
    }
    cout << endl;

    for (i = 1 ; i < n - 1 ; i++)
    {
        cout << "* ";
        for (j = 1 ; j < n - 1 ; j++)
        {
            cout << "  ";
        }
        cout << "* " << endl;
    }

    for (i = 0; i < n; i++)
    {
        cout << "* ";
    }

    return(0);
}
