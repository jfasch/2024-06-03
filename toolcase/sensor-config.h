#pragma once

#include <sensor.h>

#include <string>
#include <memory>
#include <map>


class SensorConfig
{
public:
    void add_sensor(std::string name, const std::shared_ptr<Sensor>& sensor);
    std::shared_ptr<Sensor> get_sensor(std::string name);
    void remove_sensor(std::string name);

    std::size_t size() const { return m_sensors.size(); }

private:
    std::map<std::string, std::shared_ptr<Sensor>> m_sensors;
};
