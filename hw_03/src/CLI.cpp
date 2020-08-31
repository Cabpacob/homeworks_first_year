#include "CLI.h"
#include "HuffmanException.h"
#include <vector>
#include <string>
#include <algorithm>

CLI::CLI(int argc, char *argv[])
{
    std::vector<std::string> v_args(argv, argv + argc);

    if(std::find(v_args.begin(), v_args.end(), std::string("-c")) != v_args.end())
    {
        compress_ = 1;
    }

    if(std::find(v_args.begin(), v_args.end(), std::string("-u")) != v_args.end())
    {
        extract_ = 1;
    }

    if(!(compress_ ^ extract_))
    {
        throw HuffmanException("Invalid arguments. Use only -c or only -u.");
    }


    {
        auto it = std::find(v_args.begin(), v_args.end(), "-f");

        if(it == v_args.end() || std::next(it) == v_args.end())
        {
            throw HuffmanException("Invalid arguments. Use -f <filename> to set input file.");
        }

        is_ = *std::next(it);
    }

    {
        auto it = std::find(v_args.begin(), v_args.end(), "-o");

        if(it == v_args.end() || std::next(it) == v_args.end())
        {
            throw HuffmanException("Invalid arguments. Use -o <filename> to set output file.");
        }

        os_ = *std::next(it);
    }
}

const std::string &CLI::input()
{
    return is_;
}

const std::string &CLI::output()
{
    return os_;
}

bool CLI::compress()
{
    return compress_;
}

bool CLI::extract()
{
    return extract_;
}
