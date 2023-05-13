#include "Weather.h"

Weather::Weather(int temperature, int humidity, const std::string& city)
    : m_temperature(temperature), m_humidity(humidity), m_city(city)
{ }


int Weather::get_temperature() const
{
    return m_temperature;
}

int Weather::get_humidity() const
{
    return m_humidity;
}

std::string Weather::get_city() const
{
    return m_city;
}

bool Weather::is_empty() const
{
    return m_city == " " || m_humidity == 0 || m_temperature == 0;
}