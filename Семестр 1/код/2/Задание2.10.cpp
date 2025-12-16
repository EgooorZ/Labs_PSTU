#include <iostream>
using namespace std;
int main()
{
    int k, n, max, i;
    cin >> k;

    if (k > 0)
    {
        cin >> n;
        max = n;
        for (i = 0; i < k - 1; i++)
        {
            cin >> n;
            if (n > max)
            {
                max = n;
            }
        }
        cout << max;
    }
    else
    {
        cout << "Minimum length must be >= 1";
    }
    return(0);
}
