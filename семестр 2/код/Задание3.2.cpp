#include <iostream>
#include <ctime>
using namespace std;
int main()
{
    const int n = 11;
    int tmp, p, q, i;
    int arr[n];

    cout << "before: " << endl;
    for (i = 0; i < n; i++)
    {
        arr[i] = rand();
        cout << arr[i] << " ";
    }

    cout << endl << "interval: " << endl;
    cin >> p;
    cin >> q;

    while (p < q)
    {
        tmp = arr[p];
        arr[p] = arr[q];
        arr[q] = tmp;
        q--;
        p++;
    }

    cout << endl << "after: " << endl;
    for (i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return(0);
}
