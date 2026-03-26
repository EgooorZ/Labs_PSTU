#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    const int n = 6;
    int arr[n][n];
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            arr[i][j] = rand() % 10;
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            k = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = k;
        }
    }

    cout << endl;

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