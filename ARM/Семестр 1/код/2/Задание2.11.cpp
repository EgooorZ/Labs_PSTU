#include <iostream>
using namespace std;

int main()
{
    int n, i = 0, k = 0, r;
    cin >> n;

    while (k == 0 && i < n)
    {
        cin >> k;
        i = i + 1;
    }

    if (k != 0 && i < n)
    {
        r = k;

        for (; i < n; i++)
        {
            cin >> k;
        }

        if (r > 0)
        {
            cout << "A positive number is entered first";
        }
        else
        {
            cout << "A negative number is entered earlier";
        }
        
    }
    else
    {
        cout << "The entire sequence is zeros";
    }
    
    return(0);
}
