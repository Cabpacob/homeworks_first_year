#pragma once
#include <iostream>
#include <string>

class BitReader
{
public:
    uint8_t read_to_string(std::istream &is, uint16_t bit_count, std::string &answer);
};
