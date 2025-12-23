#include <iostream>
using namespace std;
int main()
{
    int tmp, next;
    bool ordered = true;
    cin >> tmp;
    while (tmp != 0)
    {
        cin >> next;
        if (next != 0 && tmp > next)
        {
            ordered = false;
        }
        tmp = next;
    }
    if (ordered)
    {
        cout << "The sequence is ordered in ascending order!" << endl;
    }
    else
    {
        cout << "The sequence is not ordered in ascending order!" << endl;
    }
    return(0);
}
