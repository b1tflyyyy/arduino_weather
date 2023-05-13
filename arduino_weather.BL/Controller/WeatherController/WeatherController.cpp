#include "WeatherController.h"

size_t WeatherController::m_handle_response(char* ptr,
                                            size_t size,
                                            size_t nmemb,
                                            void* data)
{
    boost::property_tree::ptree* result = static_cast<boost::property_tree::ptree*>(data);

    std::stringstream ss;
    ss.write(ptr, size * nmemb);

    boost::property_tree::read_json(ss, *result);
    return size * nmemb;
}

Weather WeatherController::get_weather(const std::string& city)
{
    m_weather_url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + ",ua&units=metric&appid=" + m_api_key.get_api_key();

    m_curl = curl_easy_init();

    if (m_curl)
    {
        curl_easy_setopt(m_curl, CURLOPT_URL, m_weather_url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &WeatherController::m_handle_response);

        boost::property_tree::ptree response;
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &response);

        CURLcode code = curl_easy_perform(m_curl);
        curl_easy_cleanup(m_curl);

        if (code == CURLE_OK)
        {
            int temperature = std::ceil(response.get<float>("main.temp"));
            int humidity = response.get<int>("main.humidity");

            Weather current_weather(temperature, humidity, city);
            return current_weather;
        }
    }

    return Weather(0, 0, " ");
}