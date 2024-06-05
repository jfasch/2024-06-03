#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;


int main()
{
    int num_iterations = 10;
    std::thread t([num_iterations](){
        for (int i=0; i<num_iterations; i++) {
            std::cout << "thread: " << i << std::endl;
            std::this_thread::sleep_for(0.5s);
        }
    });

//    t.detach();
    t.join();

    std::this_thread::sleep_for(2s);
    std::cout << "main: thread terminated" << std::endl;
    
    return 0;
}
