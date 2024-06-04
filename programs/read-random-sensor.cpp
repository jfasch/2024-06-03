#include <sensor-random.h>
#include <iostream>
#include <string>


int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <MIN> MAX>\n";
        return 1;
    }

    double min = std::stod(argv[1]);
    double max = std::stod(argv[2]);

    RandomSensor s(min, max);

    std::cout << s.get_temperature() << std::endl;

    return 0;
}
