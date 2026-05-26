#include <iostream>
using namespace std;
int main()
{
    int n, i, k, minn, maxx;
    cin >> n;
    if (n >= 1)
    {
        cin >> k;
        minn = k;
        maxx = k;
        for (i = 0; i < n - 1; i++)
        {
            cin >> k;
            if (k > maxx)
            {
                maxx = k;
            }
            if (k < minn)
            {
                minn = k;
            }
        }
        cout << minn + maxx;
    }
    else
    {
        cout << "There is no sequence of this length";
    }
    return(0);
}

