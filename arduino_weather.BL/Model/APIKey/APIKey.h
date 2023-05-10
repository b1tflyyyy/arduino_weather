#pragma once
#ifndef API_KEY_H
#define API_KEY_H

#include <iostream>
#include <string>

class APIKey
{
public:
    APIKey() = default;

    ~APIKey() = default;

    std::string get_api_key();
};


#endif // _API_KEY_H_

