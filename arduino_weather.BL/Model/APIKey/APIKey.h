#pragma once
#ifndef API_KEY_H
#define API_KEY_H

#include <string>

class APIKey
{
public:
    APIKey() = default;

    ~APIKey() = default;

    static std::string get_api_key();
};


#endif // API_KEY_H

