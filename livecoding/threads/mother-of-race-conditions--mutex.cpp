#include <thread>
#include <mutex>
#include <iostream>

unsigned num_increments = 10000000;

class Integer
{
public:
    Integer(unsigned i) : _i(i) {}
    Integer& operator++() // pre-increment
    {
        std::lock_guard<std::mutex> g(_lock);
        ++_i;
        return *this;
    }
    operator unsigned int() const { return _i; }

private:
    std::mutex _lock;
    unsigned _i;
};

Integer poor_integer = 0;

static void f()
{
    for (unsigned i=0; i<num_increments; i++)
        ++poor_integer;
}

int main()
{
    std::thread t1(f);
    std::thread t2(f);

    t1.join();
    t2.join();

    std::cout << poor_integer << std::endl;
    return 0;
}
