#include "HuffmanException.h"

HuffmanException::HuffmanException(const char* error)
{
    s_ = error;
}

const char* HuffmanException::what() const noexcept
{
    return s_;
}