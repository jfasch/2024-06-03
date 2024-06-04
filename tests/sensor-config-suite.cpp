#include <sensor-const.h>
#include <sensor-random.h>
#include <sensor-config.h>
#include <gtest/gtest.h>


TEST(sensor_config_suite, basic)
{
    SensorConfig sensor_config;

    sensor_config.add_sensor("links-oben", std::make_shared<ConstantSensor>(37.5));
    sensor_config.add_sensor("rechts-unten", std::make_shared<RandomSensor>(-273.15, 100000.1));

    auto sensor = sensor_config.get_sensor("links-oben");

    ASSERT_DOUBLE_EQ(sensor->get_temperature(), 37.5);
}
