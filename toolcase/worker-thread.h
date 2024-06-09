#pragma once

#include "message-queue.h"

#include <functional>
#include <string>
#include <thread>
#include <future>


class WorkerThread
{
public:
    WorkerThread(std::string name, MessageQueue& queue, std::function<int()> work)
    : m_name(name), 
      m_queue(queue),
      m_future(m_promise.get_future()),
      m_thread([this, work]() mutable {
          int result = work();
          m_promise.set_value(result);
          
          Message message;
          message.id = Message::WORKER_COMPLETED;
          message.data = m_name;

          m_queue.PostMessage(message);
      })
    {}

    int result()
    {
        m_thread.join();
        return m_future.get();
    }

private:
    std::string m_name;
    MessageQueue& m_queue;
    std::promise<int> m_promise;
    std::future<int> m_future;
    std::thread m_thread;
};
