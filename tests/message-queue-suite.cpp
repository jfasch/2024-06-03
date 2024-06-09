#include <message-queue.h>
#include <gtest/gtest.h>


TEST(message_queue_suite, basic)
{
    MessageQueue q(1000);

    std::thread event_producer([&q](){
        Message m;
        m.id = Message::BLAH;
        q.PostMessage(m);

        m.id = Message::QUIT;
        q.PostMessage(m);
    });

    bool blah_seen = false;

    while (true)
    {
        auto message = q.GetMessage();
        if (message.id == Message::BLAH)
            blah_seen = true;
        else if (message.id == Message::QUIT)
            break;
    }

    event_producer.join();

    ASSERT_TRUE(blah_seen);
}
