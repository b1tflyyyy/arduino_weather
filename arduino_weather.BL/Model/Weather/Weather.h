#pragma once
#ifndef WEATHER_H
#define WEATHER_H

#include <string>

class Weather
{
public:
    Weather() = default;

    Weather(float temperature, float humidity, const std::string& city);

    ~Weather() = default;

    float get_temperature() const;

    float get_humidity() const;

    std::string get_city() const;

private:
    float m_temperature;
    float m_humidity;
    std::string m_city;
};

#endif /* _WEATHER_H_ */