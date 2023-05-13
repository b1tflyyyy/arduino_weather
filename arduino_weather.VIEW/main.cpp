#include "../arduino_weather.BL/Controller/WeatherController/WeatherController.h"
#include "../arduino_weather.BL/Model/Weather/Weather.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>

#define DEBUG_MODE true

#define CITY "Kropyvnytskyi"

#define BAUD_RATE 9600
#define PORT "COM3"
#define CHARACTER_SIZE 8

#define TEMP_KEY "T" /* T - Temperature */
#define HUM_KEY "H" /* H - Humidity */
#define CLEAR_KEY "C" /* C - LCD Clear */


int main()
{
    WeatherController weatherController;
    Weather weather = weatherController.get_weather(CITY);

    if (weather.is_empty())
    {
        std::cout << "===============ERROR===============\n";
        std::cout << "something went wrong, the weather is empty\n";
        return -1;
    }

#if DEBUG_MODE
    std::cout << "current temp in " << weather.get_city() << " " << weather.get_temperature() << "C" << '\n';
    std::cout << "current humidity in " << weather.get_city() << " " << weather.get_humidity() << "%" << '\n';
#endif

    try
    {
        boost::asio::io_service io;
        boost::asio::serial_port serial_port(io, PORT);
        
        serial_port.set_option(boost::asio::serial_port_base::baud_rate(BAUD_RATE));
        serial_port.set_option(boost::asio::serial_port_base::character_size(CHARACTER_SIZE));
        serial_port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

        boost::asio::write(serial_port, boost::asio::buffer(CLEAR_KEY));
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * 10));

        std::string temp = TEMP_KEY + std::to_string(weather.get_temperature());
        boost::asio::write(serial_port, boost::asio::buffer(temp));

        std::string hum = HUM_KEY + std::to_string(weather.get_humidity());
        boost::asio::write(serial_port, boost::asio::buffer(hum));

        serial_port.close();
    }
    catch (const std::exception& ex)
    {
        std::cout << "===============ERROR===============\n";
        std::cout << "something went wrong!\n";
        std::cout << "check the connection to the specified port -> " << PORT << '\n';
        std::cout << ex.what() << '\n';
    }

    return 0;
}