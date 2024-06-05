#pragma once

#include <sensor.h>

#include <string>
#include <memory>
#include <map>
#include <mutex>


class SensorConfig
{
public:
    void add_sensor_or_die_if_exists(std::string name, const std::shared_ptr<Sensor>& sensor);
    void add_sensor_if_not_exists(std::string name, const std::shared_ptr<Sensor>& sensor);
    std::shared_ptr<Sensor> get_sensor(std::string name);
    void remove_sensor(std::string name);

    // ATTENTION: do not make decisions based upon the size!
    std::size_t size() const;

private:
    std::map<std::string, std::shared_ptr<Sensor>> m_sensors;
    mutable std::mutex m_lock;
};
