#include <string>
#include <iostream>

using namespace std;

void f(int&& param)
{
    cout << "f(int&& param)" << endl;
}

void f(const int& param)
{
    cout << "f(int param)" << endl;
}

int main()
{
    f(42);

    /*const*/ int value = 42;
    f(value);

    return 0;
}
