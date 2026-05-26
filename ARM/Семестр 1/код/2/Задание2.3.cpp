#include <iostream>
using namespace std;

int main()
{
    int n, j, i, kysok, s;
    s = 0;
    cin >> n;

    for (i = 1; i <= n; i++)
    {
        for (j = i, kysok = 1; j <= 2*i; j++)
        {
            kysok = kysok * j;
        }
        s = s + kysok;
    }

    cout << s;
    return(0);
}

