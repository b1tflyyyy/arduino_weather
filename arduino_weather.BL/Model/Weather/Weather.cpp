#include "Weather.h"

Weather::Weather(float temperature, float humidity, const std::string& city)
    : m_temperature(temperature), m_humidity(humidity), m_city(city)
{ }


float Weather::get_temperature() const
{
    return m_temperature;
}

float Weather::get_humidity() const
{
    return m_humidity;
}

std::string Weather::get_city() const
{
    return m_city;
}