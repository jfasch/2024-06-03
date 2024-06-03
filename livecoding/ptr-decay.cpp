#include <iostream>

using namespace std;

void f(int array[])
{
    cout << "in der funktion: addr: " << array << endl;
}

int main()
{
    int v[] = { 1, 2, 3 };
    cout << "ausserhalb: " << v << endl;
    f(v);

    return 0;
}
