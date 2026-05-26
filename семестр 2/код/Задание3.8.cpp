#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    const int n = 11;
    int arr[n], arr2[n*2];
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }

    cout << endl;

    for (i = 0, j = 0; i < n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            arr2[j] = -1;
            j++;
        }
        arr2[j] = arr[i];
        j++;
    }

    for (i = 0; i < j; i++)
    {
        cout << arr2[i] << " ";
    }

    return(0);
}
