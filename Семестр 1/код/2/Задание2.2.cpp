#include <iostream>
using namespace std;
int main()
{
    int n, i, p;
    cin >> n;
    p = 1;
    if (n <= 0)
    {
        cout << "It is impossible to calculate the product of the first N natural numbers";
    }
    else
    {
        for (i = 1; i <= n; i++)
        {
            p = p * i;
        }

        cout << p;
    }
    return(0);
}

