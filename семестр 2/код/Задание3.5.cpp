#include <iostream>
#include <ctime>
using namespace std;
int main()
{
    const int n = 11;
    int arr[n];
    int mmax, i;

    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }

    cout << endl;
    mmax = arr[0];

    for (i = 1; i < n; i++)
    {
        if (arr[i] > mmax)
        {
            mmax = arr[i];
        }
    }

    cout << "Max:" << mmax;
    return(0);
}
