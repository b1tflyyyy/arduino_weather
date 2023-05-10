#pragma once
#ifndef _WEATHER_H_
#define _WEATHER_H_

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