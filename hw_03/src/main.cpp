#include "HuffmanArchiver.h"
#include "HuffmanException.h"
#include "CLI.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>


int main(int argc, char *argv[])
{
    try
    {
        CLI cli(argc, argv);

        std::ifstream is(cli.input(), std::ios::in | std::ios::binary);
        std::ofstream os(cli.output(), std::ios::out | std::ios::binary);

        if(!is.is_open())
            throw HuffmanException("Can't open input file");

        if(!os.is_open())
            throw HuffmanException("Can't open output file");

        HuffmanArchiver archiver;
        if(cli.compress())
        {
            auto res = archiver.compress(is, os);

            std::cout << res;
        }
        else
        {
            auto res = archiver.extract(is, os);

            std::cout << res;
        }
    }
    catch(const HuffmanException &error)
    {
        std::cout << error.what() << std::endl;
    }
    return 0;
}
