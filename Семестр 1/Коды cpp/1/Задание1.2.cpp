#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    float a, b;
    cin >> a;
    cin >> b;

    if (b != 0)
    {
        cout <<"Результат деления: "<< a / b;
    }
    else
    {
        cout << "На 0 делить нелья";
    }
    return(0);
}


