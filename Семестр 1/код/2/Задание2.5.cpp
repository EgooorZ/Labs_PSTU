#include <iostream>
using namespace std;

int main()
{
    int n, i, j;

    cin >> n;

    if (n > 2)
    {
        for (j = 0 ; j <= n; j++)
        {

            for (i = 0; i < n - j ; i++)
            {
                cout << " ";
            }

            for (i = 0; i < j ; i++)
            {
                cout << "*";
            }

            cout << endl;

        }
    }
    else
    {
        cout << "A number was entered that does not meet the condition ";
    }
    return(0);
}
