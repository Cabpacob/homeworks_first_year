#include "Resulter.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const Resulter &res)
{
    os << res.input_file_size_  << std::endl << 
          res.output_file_size_ << std::endl << 
          res.table_size_       << std::endl;
    return os;
}
