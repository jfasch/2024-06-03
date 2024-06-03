#include <sensor-const.h>
#include <sensor-config.h>
#include <gtest/gtest.h>


TEST(sensor_config_suite, basic)
{
    SensorConfig sensor_config;

    sensor_config.add_sensor("sensor1", std::make_shared<ConstantSensor>(37.5));
    sensor_config.add_sensor("sensor2", std::make_shared<ConstantSensor>(-273.15));

    auto sensor = sensor_config.get_sensor("sensor1");

    ASSERT_FLOAT_EQ(sensor->get_temperature(), 37.5);
}
