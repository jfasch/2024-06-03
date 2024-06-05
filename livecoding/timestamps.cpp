#include <chrono>
#include <iostream>

int main()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::cout << now << std::endl;
    return 0;
}
