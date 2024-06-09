#include <my-latch.h>

#include <ranges>
#include <iostream>
#include <chrono>
using namespace std::chrono_literals;


int main(int argc, char** argv)
{
    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <timeout-sec-1> ... <timeout-sec-N>" << std::endl;
        return 1;
    }

    // validate argv correctness before we start any threads and fail
    // in the middle.
    std::vector<std::chrono::duration<double>> timeouts;
    for (int i=1; i<argc; i++)
        timeouts.push_back(std::chrono::duration<double>(std::stod(argv[i])));

    MyLatch latch(timeouts.size());

    // spawn off threads to signal the latch after their respective
    // timeouts
    std::vector<std::thread> producers;
    for (std::size_t producer_no=0; auto timeout: timeouts) {
        // https://en.cppreference.com/w/cpp/ranges/enumerate_view is
        // more Pythonic, but unfortunately exists only since
        // C++23. sigh, need to keep track of producer_no manually.
        ++producer_no;
        producers.emplace_back([producer_no, timeout, &latch](){
            std::this_thread::sleep_for(timeout);
            std::cout << "producer #" << producer_no << " arriving" << std::endl;
            latch.count_down();
        });
    }

    latch.wait();
    std::cout << "consumer says \"yessss, everybody arrived\"" << std::endl;

    for (auto& producer: producers)
        producer.join();

    return 0;
}
