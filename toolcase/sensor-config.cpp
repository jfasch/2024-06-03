#include "sensor-config.h"


void SensorConfig::add_sensor(std::string name, const std::shared_ptr<Sensor>& sensor)
{
    m_sensors[name] = sensor;
}

std::shared_ptr<Sensor> SensorConfig::get_sensor(std::string name)
{
    auto found = m_sensors.find(name);
    if (found == m_sensors.end())
        return std::shared_ptr<Sensor>();
    else
        return found->second;
}

void SensorConfig::remove_sensor(std::string name)
{
    m_sensors.erase(name);
}
