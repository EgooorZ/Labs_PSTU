#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    const int n = 11;
    int arr[n];
    int i, l, k, p;

    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }

    cout << endl << "k: ";
    cin >> k;

    for (l = 0; l < k; l++)
    {
        p = arr[0];
        for (i = 0; i < n - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[n - 1] = p;
    }

    for (i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return(0);
}
