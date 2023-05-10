#include "../arduino_weather.BL/Controller/WeatherController/WeatherController.h"
#include "../arduino_weather.BL/Model/Weather/Weather.h"

#include <iostream>

int main()
{
    WeatherController weatherController;
    Weather weather = weatherController.get_weather("Kropyvnytskyi");

    std::cout << "current temp in " << weather.get_city() << " " << weather.get_temperature() << "C" << '\n';
    std::cout << "current humidity in " << weather.get_city() << " " << weather.get_humidity() << "%" << '\n';
    
    return 0;
}