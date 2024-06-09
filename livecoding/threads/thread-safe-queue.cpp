#include <thread>
#include <mutex>
#include <condition_variable>

#include <deque>
#include <iostream>
#include <chrono>
#include <cassert>

using namespace std::chrono_literals;


class Queue
{
public:
    Queue(size_t maxsize) : m_maxsize(maxsize) {}

    void put(int i)
    {
        std::unique_lock<std::mutex> guard(m_lock);
        m_not_full.wait(guard, [this](){ return m_queue.size() < m_maxsize; });
        m_queue.push_back(i);

        m_not_empty.notify_one();
    }
    int get()
    {
        int rv;

        std::unique_lock<std::mutex> guard(m_lock);

        m_not_empty.wait(guard, [this](){ return m_queue.size() > 0; });

        rv = m_queue[0];
        m_queue.pop_front();

        m_not_full.notify_one();

        return rv;
    }

private:
    size_t m_maxsize;
    std::deque<int> m_queue;

    std::mutex m_lock;
    std::condition_variable m_not_empty;
    std::condition_variable m_not_full;
};


int main()
{
    Queue q(/*maxsize*/10);

    std::thread producer1([&q](){
        int i=0;
        for (;;) {
            q.put(i++);
            std::this_thread::sleep_for(0.2s);
        }
    });

    std::thread producer2([&q](){
        int i=1000;
        for (;;) {
            q.put(i++);
            std::this_thread::sleep_for(1.3s);
        }
    });

    std::thread consumer([&q](){
        for (;;) {
            std::cout << q.get() << std::endl;
        }
    });

    producer1.join();
    producer2.join();
    consumer.join();

    return 0;
}
