
#include <iostream>
using namespace std;
int main()
{
    float n;
    cin >> n;
    if (n < 5)
        cout << n * 3;
    if (n >= 5 && n <= 7)
        cout << n / 10;
    if (n > 7)
        cout << n + 3;
    return(0);
}

