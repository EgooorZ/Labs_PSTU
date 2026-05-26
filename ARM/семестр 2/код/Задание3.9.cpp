#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    const int n = 11;
    int arr[n], arr2[n];
    int i, j = 0;

    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }

    cout << endl;

    for (i = 0; i < n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            arr2[j] = arr[i];
            j++;
        }
    }

    for (i = 0; i < j; i++)
    {
        cout << arr2[i] << " ";
    }
    return(0);
}
