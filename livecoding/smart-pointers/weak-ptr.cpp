#include "sensor-random.h"
#include "sensor-const.h"

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;
using namespace std;

int main()
{
    auto s = std::make_shared<RandomSensor>(34.4, 42.1);
    std::weak_ptr<Sensor> maybe_sensor = s;

    std::thread background_measurement(
        [s]() mutable {
            for (int i=0; i<10; i++)
                cout << s->get_temperature() << endl;
            s.reset();
        });

    s.reset();

    std::this_thread::sleep_for(1s);

    std::shared_ptr<Sensor> still_alive_sensor = maybe_sensor.lock();
    if (still_alive_sensor)
        cout << "main: " << still_alive_sensor->get_temperature() << endl;

    background_measurement.join();
    return 0;
}
