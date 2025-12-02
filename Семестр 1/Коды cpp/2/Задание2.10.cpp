#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int k, n, max, i;
    cout << "Введите длину последовательности: ";
    cin >> k;

    if (k > 0)
    {
        cout << "Введите числа последоватльности: ";
        cin >> n;
        max = n;
        for (i = 0; i < k - 1; i++)
        {
            cin >> n;
            if (n > max)
            {
                max = n;
            }
        }
        cout << "Максимальное число последовательности: " << max;
    }
    else
    {
        cout << "Минимальная длина должна быть >= 1";
    }
    return(0);
}
