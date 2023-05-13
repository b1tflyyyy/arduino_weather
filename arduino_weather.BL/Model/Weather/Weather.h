#pragma once
#ifndef WEATHER_H
#define WEATHER_H

#include <string>

class Weather
{
public:
    Weather() = default;

    Weather(int temperature, int humidity, const std::string& city);

    ~Weather() = default;

    int get_temperature() const;

    int get_humidity() const;

    std::string get_city() const;

    bool is_empty() const;

private:
    int m_temperature;
    int m_humidity;
    std::string m_city;
};

#endif /* _WEATHER_H_ */