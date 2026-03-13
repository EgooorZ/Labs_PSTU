#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    const int n = 11;
    int arr[n];
    int mmin, mmax, i;

    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }

    cout << endl;
    mmin = arr[0];
    mmax = arr[0];

    for (i = 1; i < n; i++)
    {
        if (arr[i] < mmin)
        {
            mmin = arr[i];
        }
        else if (arr[i] > mmax)
        {
            mmax = arr[i];
        }
    }

    cout << "Min: " << mmin << endl << "Max: " << mmax;
    return(0);
}
