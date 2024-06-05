#include <thread>
#include <future>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;


int main()
{
    std::promise<int> to_main_1;
    auto from_thread_1 = to_main_1.get_future();

    std::promise<int> to_thread;
    auto from_main = to_thread.get_future();

    std::promise<int> to_main_2;
    auto from_thread_2 = to_main_2.get_future();

    std::thread t([my_to_main_1=std::move(to_main_1),
                   my_from_main=std::move(from_main),
                   my_to_main_2=std::move(to_main_2)]() mutable {
        std::this_thread::sleep_for(3.6s);
        my_to_main_1.set_value(42);

        int main_told_me = my_from_main.get();
        std::cout << "main_told_me: " << main_told_me << std::endl;

        std::this_thread::sleep_for(0.3s);
        my_to_main_2.set_value(666);
    });

    int result;

    result = from_thread_1.get();
    std::cout << result << std::endl;

    to_thread.set_value(-5);

    result = from_thread_2.get();
    std::cout << result << std::endl;

    t.join();

    return 0;
}
