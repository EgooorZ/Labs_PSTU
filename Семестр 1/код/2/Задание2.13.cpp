#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a, b, c, D;
    float x1, x2;
    cin >> a;
    cin >> b;
    cin >> c;
    D = pow(b, 2) - 4 * a * c;

    if (D > 0)
    {
        x1 = ((-b) + sqrt(D)) / (2 * a);
        x2 = ((-b) - sqrt(D)) / (2 * a);
        cout << "Roots equation: " << x1 << ", " << x2;
    }
    else if (D == 0)
    {
        x1 = (-b) / (2 * a);
        cout << "Root equation: " << x1;
    }
    else
    {
        cout << "no roots";
    }

    return(0);
}
