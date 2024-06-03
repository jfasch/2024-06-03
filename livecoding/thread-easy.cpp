#include <thread>
#include <iostream>


int main()
{
    std::thread t([](){ for (int i=0; i<10; i++) std::cout << i << std::endl; });
    t.join();
    return 0;
}
