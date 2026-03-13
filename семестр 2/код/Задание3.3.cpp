#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    const int n = 11;
    int max, count = 1, i;
    int arr[n];

    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }

    cout << endl;
    max = arr[0];

    for (i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
        else if (arr[i] == max)
        {
            count = count + 1;
        }
    }

    cout << "maximum element: " << max << endl;
    cout << "the number of elements with this value: " << count;
    return(0);
}
