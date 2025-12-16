#include <iostream>
using namespace std;

int main()
{
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
        cout << "A number was entered that does not meet the condition";
    }
    return(0);
}

