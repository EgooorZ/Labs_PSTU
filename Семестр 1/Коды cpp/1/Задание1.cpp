
#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int a, b, c;
    cin >> a;
    cin >> b;
    cin >> c;

    cout << "Наибольшее число из введенных чисел: ";
        if (a > b)
        {
            if (a > c)
                cout << a;
            else
                cout << c;
        }
        else
        {
            if (b > c)
                cout << b;
            else
                cout << c;
        }

    
    return(0);
}
