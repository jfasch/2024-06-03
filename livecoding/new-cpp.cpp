#include <map>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <variant>


using namespace std::chrono_literals;

class TodoList final
{
public:
    TodoList(std::initializer_list<std::pair<std::string /*name*/,
                                             std::function<void()>
             >> list)
    {
        for (auto [name, func]: list)
            _list[name] = func;                  
    }

    TodoList() = default;

    TodoList(const TodoList&) = delete;
    TodoList& operator=(const TodoList&) = delete;

    void start()
    {
        for (auto& [name, item]: _list) {
            std::cout << "NAME: " << name << " starting\n";

            std::shared_ptr<std::thread> t(new std::thread(std::get<0>(item)));
            item = t;
        }
    }
        
    void wait()
    {
        for (const auto& [name, item]: _list)
            std::get<1>(item)->join();
    }


private:
    using todo_list = std::map<std::string, 
                               std::variant<std::function<void()>, std::shared_ptr<std::thread>>
                               >;

    todo_list _list;
};


int main()
{
    TodoList tdl = {
        { "up 1 to 10",
          [](){
              for (int i=1; i<=10; i++) {
                  std::cout << "UP: " << i << '\n';
                  std::this_thread::sleep_for(1s);
              }
          },
        },
        { "down 1000 to 980",
          [](){
              for (int i=1000; i>=980; i--) {
                  std::cout << "DOWN: " << i << '\n';
                  std::this_thread::sleep_for(0.5s);
              }
          },
        },
    };

    tdl.start();
    tdl.wait();

    return 0;
}
