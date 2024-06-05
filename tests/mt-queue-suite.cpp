#include <queue.h>

#include <gtest/gtest.h>
#include <thread>


TEST(queue_suite, basic)
{
    Queue<int> q(10);

    std::thread producer([&q](){
        for (int i=0; i<5; i++)
            q.put(i);
    });

    ASSERT_EQ(q.get(), 0);
    ASSERT_EQ(q.get(), 1);
    ASSERT_EQ(q.get(), 2);
    ASSERT_EQ(q.get(), 3);
    ASSERT_EQ(q.get(), 4);

    producer.join();
}
