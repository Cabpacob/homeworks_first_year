#pragma once

#include <exception>

class HuffmanException : public std::exception
{
public:
    HuffmanException(const char* error);

    const char* what() const noexcept override;
private:
    const char* s_;
};