#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    const int n = 6;
    int arr[n][n];
    int i, j, k, tmp, num = 0;

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

    cin >> k;
    cout << endl;
    k = k - 1;

    for (i = 0; i < n; i++)
    {
        tmp = arr[k][i];
        num = i;

        for (j = i; j < n; j++)
        {
            if (arr[k][j] < tmp)
            {
                tmp = arr[k][j];
                num = j;
            }
        }

        for (j = 0; j < n; j++)
        {
            tmp = arr[j][i];
            arr[j][i] = arr[j][num];
            arr[j][num] = tmp;
        }
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