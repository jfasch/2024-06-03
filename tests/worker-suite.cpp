#include <message-queue.h>
#include <worker-thread.h>

#include <gtest/gtest.h>


TEST(worker_thread_suite, basic)
{
    MessageQueue q(1000);

    WorkerThread deep_thought("deep-thought", q, [](){
        // after 7.5 million years ...
        return 42;
    });

    while (true) {
        auto message = q.GetMessage();

        if (message.id == Message::WORKER_COMPLETED && get<std::string>(message.data) == "deep-thought") {
            ASSERT_EQ(deep_thought.result(), 42);
            break;
        }
    }
}
