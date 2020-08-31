
#pragma once
#include <iostream>
#include <fstream>

class CLI
{
public:
    CLI(int argc, char *argv[]);
    const std::string &input();
    const std::string &output();
    bool compress();
    bool extract();

private:
    std::string is_;
    std::string os_;
    bool compress_ = 0;
    bool extract_ = 0;
};
