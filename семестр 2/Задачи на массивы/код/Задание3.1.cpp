#include <iostream>
#include <ctime>
using namespace std;

int main()
{

    const int n = 4;
    int tmp, i;
    int arr[n];

    cout << "before: " << endl;

    for (i = 0; i < n; i++)
    {
        arr[i] = rand();
        cout << arr[i] << " ";
    }

    for (i = 0; i < n/2; i++)
    {
        tmp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = tmp;
    }

    cout << endl << "after: " << endl;
    for (i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return(0);
}
