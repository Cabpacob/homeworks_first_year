#include "doctest.h"
#include "CLI.h"
#include <vector>

TEST_CASE("Compress") 
{
    const char* args[] = {"-c", "-f", "input.txt", "-o", "output.txt"};
    CLI cli(5, (char**)args);

    CHECK(cli.compress());
    CHECK(!cli.extract());
    CHECK(cli.input() == "input.txt");
    CHECK(cli.output() == "output.txt");
};

TEST_CASE("Compress shuffle arguments 1") 
{
    const char* args[] = {"-o", "output.txt", "-c", "-f", "input.txt"};
    CLI cli(5, (char**)args);

    CHECK(cli.compress());
    CHECK(!cli.extract());
    CHECK(cli.input() == "input.txt");
    CHECK(cli.output() == "output.txt");
};

TEST_CASE("Compress shuffle arguments 2") 
{
    const char* args[] = {"-o", "output.txt", "-f", "input.txt", "-c"};
    CLI cli(5, (char**)args);

    CHECK(cli.compress());
    CHECK(!cli.extract());
    CHECK(cli.input() == "input.txt");
    CHECK(cli.output() == "output.txt");
};

TEST_CASE("Extract") 
{
    const char* args[] = {"-u", "-f", "input.txt", "-o", "output.txt"};
    CLI cli(5, (char**)args);

    CHECK(cli.extract());
    CHECK(!cli.compress());
    CHECK(cli.input() == "input.txt");
    CHECK(cli.output() == "output.txt");
};

TEST_CASE("Extract shuffle arguments 1") 
{
    const char* args[] = {"-o", "output.txt", "-u", "-f", "input.txt"};
    CLI cli(5, (char**)args);

    CHECK(cli.extract());
    CHECK(!cli.compress());
    CHECK(cli.input() == "input.txt");
    CHECK(cli.output() == "output.txt");
};

TEST_CASE("Extract shuffle arguments 2") 
{
    const char* args[] = {"-o", "output.txt", "-f", "input.txt", "-u"};
    CLI cli(5, (char**)args);

    CHECK(cli.extract());
    CHECK(!cli.compress());
    CHECK(cli.input() == "input.txt");
    CHECK(cli.output() == "output.txt");
};
