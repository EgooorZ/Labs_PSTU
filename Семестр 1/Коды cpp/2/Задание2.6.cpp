#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n, i, j;

    cin >> n;

    if (n > 2)
    {
        for (j = n; j > 0 ; j--)
        {

            for (i = 0; i < n - j; i++)
            {
                cout << " ";
            }

            for (i = 0; i < j; i++)
            {
                cout << "*";
            }

            cout << endl;

        }
    }
    else
    {
        cout << "Введено число не по условию ";
    }
    return(0);
}