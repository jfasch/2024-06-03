#include "sensor-config.h"


void SensorConfig::add_sensor(std::string name, const std::shared_ptr<Sensor>& sensor)
{
    m_sensors[name] = sensor;
}

std::shared_ptr<Sensor> SensorConfig::get_sensor(std::string name)
{
    return m_sensors[name];
}
