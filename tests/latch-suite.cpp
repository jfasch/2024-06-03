#include <my-latch.h>

#include "gtest/gtest.h"

#include <chrono>
#include <string>
#include <thread>
#include <future>
#include <vector>

using namespace std::chrono_literals;


TEST(my_latch_suite, basic)
{
    const std::vector<std::string> expected_results = {
        "producer one finished",
        "producer two finished",
        "consumer returned from wait"
    };
    std::mutex m_results_lock;
    std::vector<std::string> results;
    MyLatch l(2);

    std::thread producerOne([&l, &results, &m_results_lock, msg=expected_results[0]](){
        std::this_thread::sleep_for(0.02s);
        {
            std::unique_lock<std::mutex> g(m_results_lock);
            results.emplace_back(msg);
        }
        l.count_down();
    });

    std::thread producerTwo([&l, &results, &m_results_lock, msg=expected_results[1]](){
        std::this_thread::sleep_for(0.01s);
        {
            std::unique_lock<std::mutex> g(m_results_lock);
            results.emplace_back(msg);
        }
        l.count_down();
    });

    std::thread consumer([&l, &results, &m_results_lock, msg=expected_results[2]](){
        l.wait();
        {
            std::unique_lock<std::mutex> g(m_results_lock);
            results.emplace_back(msg);
        }
    });

    producerOne.join();
    producerTwo.join();
    consumer.join();

    ASSERT_EQ(expected_results.size(), results.size());
    for (const auto& item : results)
    {
        ASSERT_NE(std::find(expected_results.cbegin(), expected_results.cend(), item), expected_results.cend());
    }
    ASSERT_EQ(expected_results.back(), results.back()); // expect consumer to be last
}

TEST(my_latch_suite, something_more_elaborate_but_also_more_deterministic)
{
    MyLatch latch(1);

    std::promise<void> kick_him_loose;

    std::thread arriver([&latch, 
                         kicked=std::move(kick_him_loose.get_future())
                        ]() mutable {
        kicked.get();
        latch.count_down();
    });

    // arriver has not been kicked loose, so he must not have arrived.
    ASSERT_FALSE(latch.try_wait());

    kick_him_loose.set_value();

    // now he should
    latch.wait();

    ASSERT_TRUE(latch.try_wait()); // btw, when we wait()ed, then
                                   // try_wait() should be successful.

    arriver.join();
}
