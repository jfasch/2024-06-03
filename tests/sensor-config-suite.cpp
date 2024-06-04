#include <sensor-const.h>
#include <sensor-config.h>
#include <gtest/gtest.h>


TEST(sensor_config_suite, basic)
{
    SensorConfig sensor_config;

    sensor_config.add_sensor("links-oben", std::make_shared<ConstantSensor>(37.5));
    sensor_config.add_sensor("rechts-unten", std::make_shared<ConstantSensor>(-273.15));

    auto sensor = sensor_config.get_sensor("links-oben");

    ASSERT_FLOAT_EQ(sensor->get_temperature(), 37.5);
}
