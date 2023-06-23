#pragma once
#ifndef WEATHER_CONTROLLER_H
#define WEATHER_CONTROLLER_H

#define CURL_STATICLIB

#include <curl.h>

#ifdef _DEBUG
#pragma comment (lib, "../x64_curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "../x64_curl/libcurl_a.lib")
#endif

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")

#include <string>
#include <sstream>
#include <cmath>

#include <json/json.hpp>

#include "../arduino_weather.BL/Model/Weather/Weather.h"
#include "../arduino_weather.BL/Model/APIKey/APIKey.h"


class WeatherController
{
public:
    WeatherController(const std::string& city);

    ~WeatherController() = default;

    Weather get_weather();

private:
    static size_t m_handle_response(char* ptr,
                                    size_t size,
                                    size_t nmemb,
                                    void* data);

    CURL* m_curl;
    std::string m_weather_url;
    std::string m_city;
};


#endif /* _WEATHER_CONTROLLER_H_ */

