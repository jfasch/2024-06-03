#pragma once

#include "queue.h"

#include <variant>

struct point
{
    int x, y;
};

struct Message
{
    enum ID {
        BLAH,
        WORKER_COMPLETED,
        MOUSE_CLICK,
        QUIT,
    };

    ID id;
    std::variant<std::string, point> data;
};

class MessageQueue
{
public:
    MessageQueue(size_t maxsize) : m_queue(maxsize) {}

    void PostMessage(const Message& m) { m_queue.put(m); }
    Message GetMessage() { return m_queue.get(); }

private:
    Queue<Message> m_queue;
};
