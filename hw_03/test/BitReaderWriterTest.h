#include "doctest.h"
#include "BitReader.h"
#include "BitWriter.h"
#include <string>

TEST_CASE("Test write") 
{
    BitWriter writer;
    std::stringstream os;

    std::string binary_text = "00000000111111111000000000000001";

    for(const auto &bit : binary_text)
        writer.write(bit - '0', os);


    CHECK(os.str().size() == 4);
    CHECK((uint8_t)os.str()[0] == 0);
    CHECK((uint8_t)os.str()[1] == 255);
    CHECK((uint8_t)os.str()[2] == 1);
    CHECK((uint8_t)os.str()[3] == 128);
};

TEST_CASE("Test read") 
{
    BitWriter writer;
    std::stringstream os("0123");

    BitReader reader;

    std::string text;
    reader.read_to_string(os, 32, text);

    CHECK(text == "00001100100011000100110011001100"); //48, 49, 50, 51
};

TEST_CASE("Test read") 
{
    BitWriter writer;
    std::stringstream os;

    std::string binary_text = "0101001111011000001010100111100001010011111000001010111010100000";

    for(const auto &bit : binary_text)
        writer.write(bit - '0', os);

    BitReader reader;

    std::string text;
    reader.read_to_string(os, 64, text);

    CHECK(text == binary_text);
};

