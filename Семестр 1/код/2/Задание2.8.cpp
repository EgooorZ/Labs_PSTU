#include <iostream>
using namespace std;

int main()
{
    int n, i, j;
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
        cout << "Length must be >2";
    }
    return(0);
}
