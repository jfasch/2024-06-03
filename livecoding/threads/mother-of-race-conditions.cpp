#include <thread>
#include <atomic>
#include <iostream>

unsigned num_increments = 10000000;
unsigned poor_integer = 0;

static void f()
{
    for (unsigned i=0; i<num_increments; i++)
        ++poor_integer;
}

int main()
{
    std::thread t1(f);
    std::thread t2(f);

    t1.join();
    t2.join();

    std::cout << poor_integer << std::endl;
    return 0;
}
