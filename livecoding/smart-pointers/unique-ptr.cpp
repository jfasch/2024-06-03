#include "sensor-random.h"
#include "sensor-const.h"

#include <iostream>
#include <map>
#include <string>
#include <memory>

using namespace std;

int main()
{
    std::map<std::string, std::unique_ptr<Sensor>> sensors;

    auto s1 = std::make_unique<RandomSensor>(34.4, 42.1);
    
    // startup
    sensors["links-unten"] = std::move(s1);
    sensors["rechts-oben"] = std::make_unique<ConstantSensor>(-273.15);

    // runtime
    for (const auto& [name, sensor]: sensors)
        cout << name << ": " << sensor->get_temperature() << endl;

    // cout << "von der seite: " << s1->get_temperature() << endl;

    return 0;
}
