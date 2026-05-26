#include <iostream>
using namespace std;
int main()
{
    float a, b;
    cin >> a;
    cin >> b;

    if (b != 0)
    {
        cout << a / b;
    }
    else
    {
        cout << "You can't divide by 0";
    }
    return(0);
}


