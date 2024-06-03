#include <algorithm>
#include <functional>
#include <iostream>


class MySystem
{
public:
    MySystem(std::function<void(const std::string&)> logger) : _logger(logger) {}

    void do_one_thing()
    {
        _logger("doing one thing");
    }
    void do_another_thing()
    {
        _logger("doing another thing");
    }

private:
    std::function<void(const std::string&)> _logger;
};

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <LOGGING-PREFIX>\n";
        return 1;
    }

    std::string logging_prefix = argv[1];

    MySystem system([logging_prefix](const std::string& msg){
        std::cout << logging_prefix << ':' << msg << std::endl;
    });

    system.do_one_thing();
    system.do_another_thing();

    return 0;
}
