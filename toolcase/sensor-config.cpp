#include "sensor-config.h"


void SensorConfig::add_sensor_or_die_if_exists(std::string name, const std::shared_ptr<Sensor>& sensor)
{
    std::lock_guard<std::mutex> g(m_lock);

    auto [_, inserted] = m_sensors.insert(std::make_pair(name, sensor));
    if (inserted)
        return;
    else
        throw std::runtime_error("nix add");
}

void SensorConfig::add_sensor_if_not_exists(std::string name, const std::shared_ptr<Sensor>& sensor)
{
    std::lock_guard<std::mutex> g(m_lock);

    m_sensors.insert(std::make_pair(name, sensor));
}

std::shared_ptr<Sensor> SensorConfig::get_sensor(std::string name)
{
    std::lock_guard<std::mutex> g(m_lock);

    auto found = m_sensors.find(name);
    if (found == m_sensors.end())
        return std::shared_ptr<Sensor>();
    else
        return found->second;
}

void SensorConfig::remove_sensor(std::string name)
{
    std::lock_guard<std::mutex> g(m_lock);

    m_sensors.erase(name);
}

std::size_t SensorConfig::size() const
{ 
    std::lock_guard<std::mutex> g(m_lock);

    return m_sensors.size();
}
