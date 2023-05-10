#pragma once
#ifndef _API_KEY_H_
#define _API_KEY_H_

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

