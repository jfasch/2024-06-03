#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>


template <typename T>
class Queue
{
public:
    Queue(size_t maxsize) : m_maxsize(maxsize) {}

    void put(const T& elem)
    {
        std::unique_lock<std::mutex> guard(m_lock);
        m_not_full.wait(guard, [this](){ return m_queue.size() < m_maxsize; });
        m_queue.push_back(elem);

        m_not_empty.notify_one();
    }
    T get()
    {
        std::unique_lock<std::mutex> guard(m_lock);
        m_not_empty.wait(guard, [this](){ return m_queue.size() > 0; });

        T rv = m_queue[0];
        m_queue.pop_front();

        m_not_full.notify_one();

        return rv;
    }

private:
    size_t m_maxsize;
    std::deque<T> m_queue;

    std::mutex m_lock;
    std::condition_variable m_not_empty;
    std::condition_variable m_not_full;
};
