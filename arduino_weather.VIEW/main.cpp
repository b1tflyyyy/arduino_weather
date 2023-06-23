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
    try
    {
        Weather weather;
        WeatherController weatherController(CITY);

        boost::asio::io_service io;
        boost::asio::serial_port serial_port(io, PORT);
        
        serial_port.set_option(boost::asio::serial_port_base::baud_rate(BAUD_RATE));
        serial_port.set_option(boost::asio::serial_port_base::character_size(CHARACTER_SIZE));
        serial_port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

        std::string temp;
        std::string hum;
       
    #if DEBUG_MODE
        unsigned int counter = 0;
    #endif

        for (;;)
        {
            using namespace std::chrono_literals;

            weather = weatherController.get_weather();
            if (weather.is_empty())
            {
                std::cout << "===============ERROR===============\n";
                std::cout << "something went wrong, the weather is empty\n";
                return -1;
            }

            boost::asio::write(serial_port, boost::asio::buffer(CLEAR_KEY));
            std::this_thread::sleep_for(1s);

            temp = TEMP_KEY + std::to_string(weather.get_temperature());
            boost::asio::write(serial_port, boost::asio::buffer(temp));

            hum = HUM_KEY + std::to_string(weather.get_humidity());
            boost::asio::write(serial_port, boost::asio::buffer(hum));

        #if DEBUG_MODE
            std::cout << "Received data from server --->\n";
            std::cout << "current temp in " << weather.get_city() << " " << weather.get_temperature() << "C" << '\n';
            std::cout << "current humidity in " << weather.get_city() << " " << weather.get_humidity() << "%" << "\n\n";

            std::cout << "Data in variables ---> \n";
            std::cout << "temp: " << temp << '\n';
            std::cout << "hum: " << hum << '\n';
            std::cout << "city: " << CITY << '\n';

            std::cout << "Data sending counter: " << ++counter << "\n\n";
        #endif

            std::this_thread::sleep_for(10min);
        }
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