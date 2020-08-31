#include "doctest.h"
#include "HuffmanArchiver.h"
#include <string>
#include <iostream>

TEST_CASE("Only one simbol") 
{
    std::stringstream in("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    std::stringstream out;

    HuffmanArchiver h;

    h.compress(in, out);

    std::stringstream in_copy;

    h.extract(out, in_copy);

    CHECK(in.str() == in_copy.str());

};

TEST_CASE("Random") 
{
    std::stringstream in("FhdgjhfzdhoHAYUFDYhgsvdhesjfygkwajhdkqwduiqwvdhjhBJHDVSBJdnqldhqwidvcdjsahdblQWPEQPI412YTY3`2R2");
    std::stringstream out;

    HuffmanArchiver h;

    h.compress(in, out);

    std::stringstream in_copy;

    h.extract(out, in_copy);

    CHECK(in.str() == in_copy.str());

};

TEST_CASE("Numbers with spaces") 
{
    std::stringstream in("228 322 1337");
    std::stringstream out;

    HuffmanArchiver h;

    h.compress(in, out);

    std::stringstream in_copy;

    h.extract(out, in_copy);

    CHECK(in.str() == in_copy.str());

};

TEST_CASE("Numbers with endls") 
{
    std::stringstream in("228\n322\n1337");
    std::stringstream out;

    HuffmanArchiver h;

    h.compress(in, out);

    std::stringstream in_copy;

    h.extract(out, in_copy);

    CHECK(in.str() == in_copy.str());

};

TEST_CASE("Binary files") 
{
    std::stringstream in("228\n322\n1337", std::ios::in | std::ios::binary);
    std::stringstream out(std::ios::out | std::ios::in | std::ios::binary);

    HuffmanArchiver h;

    h.compress(in, out);

    std::stringstream in_copy(std::ios::out | std::ios::binary);

    h.extract(out, in_copy);

    CHECK(in.str() == in_copy.str());

};
