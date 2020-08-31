#pragma once

#include <iostream>

class BitWriter
{
public:
    BitWriter() = default;

    bool write(bool bit, std::ostream &os);
    bool dump(std::ostream &os);
private:
    int count = 0;
    uint8_t buffer = 0;
};
