
#pragma once
// #include <stdint>
#include <iostream>

class Resulter
{
public:
    Resulter() = default;
    Resulter(size_t input, size_t output, size_t table) : input_file_size_(input), output_file_size_(output), table_size_(table) {};
    friend std::ostream &operator<<(std::ostream &os, const Resulter &res);
private:
    size_t input_file_size_  = 0;
    size_t output_file_size_ = 0;
    size_t table_size_       = 0;
};
