#include <iostream>

using namespace std;

int main()
{
    int i = 42;
    auto pi = &i;
    (void)pi;

    cout << "&i:" << &i << endl;
    cout << "pi:" << pi << endl;

    return 0;
}
