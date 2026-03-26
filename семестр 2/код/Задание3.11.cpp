#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    const int n = 5;
    int arr[n][n];
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            arr[i][j] = rand() % 10;
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (i = 0; i < n; i++)
    {
        arr[i][i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return(0);
}

