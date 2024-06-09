#pragma once

#include <mutex>
#include <condition_variable>


class MyLatch
{
public:
    MyLatch(std::size_t number_of_producers) :
        m_number_of_producers(number_of_producers)
    {
    }

    void count_down()
    {
        std::unique_lock<std::mutex> g(m_lock);
        --m_number_of_producers;
        if (m_number_of_producers == 0)
            m_not_zero.notify_all();
    }

    void wait()
    {
        std::unique_lock<std::mutex> g(m_lock);
        m_not_zero.wait(g, [this](){
            return m_number_of_producers == 0;
        });
    }

    // note that try_wait() is of rather limited use. the only
    // conclusive answer it can give is whether all producers have
    // arrived.

    // if it says "no, not everybody has arrived", then this statement
    // could not be valid anymore at the time you make decisions based
    // on it.
    bool try_wait()
    {
        std::lock_guard<std::mutex> g(m_lock);
        return m_number_of_producers == 0;
    }

private:
    std::size_t m_number_of_producers;
    std::condition_variable m_not_zero;
    std::mutex m_lock;
};
