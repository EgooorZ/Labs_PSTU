#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n, i, j;
    cin >> n;
    
    cout << "N stars" << endl;
    for (i = 0 ;i < sqrt(n); i++)
    {
        for (j = 0; j < sqrt(n); j++)
        {
            cout << "* ";
        }
        cout << endl;
    }

    cout << endl << "Filled square with side N" << endl;
    for (i = 0 ; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << "* ";
        }
        cout << endl;
    }


    cout << endl << "Empty square with side N" << endl;
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
