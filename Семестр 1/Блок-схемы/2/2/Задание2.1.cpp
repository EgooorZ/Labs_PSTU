#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    if (n <= 0)
    {
        cout << "it is impossible to calculate the sum of the first N natural numbers";
    }
    else
    {
        cout << (n * (n + 1)) / 2;
    }
    return(0);
}

