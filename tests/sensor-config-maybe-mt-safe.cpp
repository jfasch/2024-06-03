#include <sensor-config.h>
#include <sensor-const.h>
#include <thread>

int main()
{
    SensorConfig config;

    std::thread adder1([&config](){
        for (;;) {
            config.add_sensor_if_not_exists("name1", std::make_shared<ConstantSensor>(37.5));
        }
    });

    std::thread adder2([&config](){
        for (;;) {
            config.add_sensor_if_not_exists("name1", std::make_shared<ConstantSensor>(37.5));
        }
    });

    std::thread remover([&config](){
        for (;;) {
            auto s = config.get_sensor("name1");
            if (s)
                config.remove_sensor("name1");
        }
    });

    std::thread measurer([&config](){
        for (;;) {
            auto s = config.get_sensor("name1");
            if (s)
                s->get_temperature();
        }
    });

    adder1.join();
    adder2.join();
    remover.join();
    measurer.join();

    return 0;
}
