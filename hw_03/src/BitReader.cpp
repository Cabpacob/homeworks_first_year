#include "BitReader.h"

#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>

uint8_t BitReader::read_to_string(std::istream &is, uint16_t bit_count, std::string &answer)
{
    uint16_t ceil_bytes = (bit_count / 8) + !!(bit_count % 8);

    for(uint16_t i = 0; i < ceil_bytes; i++)
    {
        uint8_t byte;
        is.read((char*)&byte, sizeof(byte));
        std::string binary;

        for(int bit = 0; bit < 8; bit++)
            binary += ('0' + !!(byte & (1 << bit)));
        answer += binary;
    }
    answer.resize(bit_count);
    return ceil_bytes;
}
