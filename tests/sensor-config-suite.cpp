#include <sensor-const.h>
#include <sensor-random.h>
#include <sensor-config.h>
#include <gtest/gtest.h>


TEST(sensor_config_suite, basic)
{
    SensorConfig sensor_config;

    sensor_config.add_sensor("links-oben", std::make_shared<ConstantSensor>(37.5));
    sensor_config.add_sensor("rechts-unten", std::make_shared<RandomSensor>(-273.15, 100000.1));

    auto lo = sensor_config.get_sensor("links-oben");

    ASSERT_DOUBLE_EQ(lo->get_temperature(), 37.5);

    auto ru = sensor_config.get_sensor("rechts-unten");

    double temperature = ru->get_temperature();

    ASSERT_GE(temperature, -273.15);
    ASSERT_LE(temperature, 100000.1);
}

TEST(sensor_config_suite, notfound)
{
    SensorConfig config;
    auto s = config.get_sensor("notexist");
    ASSERT_FALSE(s);
    ASSERT_EQ(config.size(), 0);
}

TEST(sensor_config_suite, remove)
{
    SensorConfig config;

    config.add_sensor("links-oben", std::make_shared<ConstantSensor>(37.5));

    auto s = config.get_sensor("links-oben");
    ASSERT_TRUE(s);

    config.remove_sensor("links-oben");

    s = config.get_sensor("links-oben");
    ASSERT_FALSE(s);

    ASSERT_EQ(config.size(), 0); // btw
}

TEST(sensor_config_suite, size)
{
    SensorConfig config;
    ASSERT_EQ(config.size(), 0);
    config.add_sensor("links-oben", std::make_shared<ConstantSensor>(37.5));
    ASSERT_EQ(config.size(), 1);
    config.add_sensor("rechts-unten", std::make_shared<ConstantSensor>(666));
    ASSERT_EQ(config.size(), 2);

    config.remove_sensor("rechts-unten");
    ASSERT_EQ(config.size(), 1);

    auto s = config.get_sensor("links-oben");
    ASSERT_TRUE(s);
    ASSERT_FLOAT_EQ(s->get_temperature(), 37.5);
}
