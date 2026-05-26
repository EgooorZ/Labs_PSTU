#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    const int n = 11;
    int arr[n], i;
    bool sorted = true;

    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }

    cout << endl;
    
    for (i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            sorted = false;
            break;
        }
    }

    if (sorted)
    {
        cout << "the array is sorted";
    }
    else
    {
        cout << "the array is not sorted in ascending order";
    }
    return(0);
}
