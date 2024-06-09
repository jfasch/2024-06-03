#include <message-queue.h>
#include <worker-thread.h>

#include <chrono>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;


int main()
{
    MessageQueue queue(100);

    WorkerThread deep_thought("deep-thought", queue, [](){
        // after 7.5 million years ...
        std::this_thread::sleep_for(3s);
        return 42;
    });

    WorkerThread lazy_satan("satan", queue, [](){
        std::this_thread::sleep_for(6s);
        return 666;
    });

    std::thread user_clicking_about_on_screen([&queue](){
        int x = 0, y = 1;
        while (true) {
            Message message;
            message.id = Message::MOUSE_CLICK;
            message.data = point(x, y);
            queue.PostMessage(message);

            x += 1;
            y *= 2;

            std::this_thread::sleep_for(0.5s);
        }
    });

    while (true) {
        auto message = queue.GetMessage();
        if (message.id == Message::QUIT)
            break;
        else if (message.id == Message::MOUSE_CLICK) {
            auto coord = std::get<point>(message.data);
            std::cout << "MOUSE_CLICK: (" << coord.x << ',' << coord.y << ')' << std::endl;
        }
        else if (message.id == Message::WORKER_COMPLETED) {
            auto worker_name = std::get<std::string>(message.data);
            if (worker_name == "deep-thought")
                std::cout << "WORKER_COMPLETED: name=" << worker_name << ", result=" << deep_thought.result() << std::endl;
            else if (worker_name == "satan")
                std::cout << "WORKER_COMPLETED: name=" << worker_name << ", result=" << lazy_satan.result() << std::endl;
            else
                std::cout << "WORKER_COMPLETED: name=" << worker_name << " (uiuiui)" << std::endl;
        }
    }
}
