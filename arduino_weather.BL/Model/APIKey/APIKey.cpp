#include "APIKey.h"

std::string APIKey::get_api_key()
{
    FILE* fs;
    errno_t code = fopen_s(&fs, "api_key.txt", "r");

    if (code != 0)
    {
        return "";
    }

    std::string api_key;
    int character = fgetc(fs);
    while (character != EOF)
    {
        api_key += static_cast<char>(character);
        character = fgetc(fs);
    }

    fclose(fs);
    return api_key;
}