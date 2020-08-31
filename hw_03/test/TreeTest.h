#include "doctest.h"
#include "Tree.h"
#include "HuffmanArchiver.h"
#include <vector>
#include <random>
#include <string>

TEST_CASE("Two different groups") 
{
    std::vector<int> cnt(256);
    cnt[100] = 1000;
    cnt[50]  = 1;

    Tree tr(cnt);
    auto compress = tr.compress();
    CHECK(compress[100] == "1");
    CHECK(compress[50] == "0");
};

TEST_CASE("Three different groups") 
{
    std::vector<int> cnt(256);
    cnt[100] = 4;
    cnt[50]  = 1;
    cnt[25]  = 2;

    Tree tr(cnt);
    auto compress = tr.compress();
    CHECK(compress[25]  == "01");
    CHECK(compress[50]  == "00");
    CHECK(compress[100] == "1");
};


TEST_CASE("Four different groups") 
{
    std::vector<int> cnt(256);
    cnt[100] = 1000;
    cnt[50]  = 100;
    cnt[25]  = 10;
    cnt[12]  = 1;

    Tree tr(cnt);
    auto compress = tr.compress();
    CHECK(compress[100] == "1");
    CHECK(compress[50]  == "01");
    CHECK(compress[25]  == "001");
    CHECK(compress[12]  == "000");
};


TEST_CASE("Test prefix code") 
{
    std::vector<int> cnt(256);
    std::mt19937 rnd(1337);

    for(auto &i : cnt)
        i = rnd() % 1000;

    Tree tr(cnt);
    auto compress = tr.compress();

    for(size_t i = 0; i < compress.size(); i++)
        for(size_t j = i + 1; j < compress.size(); j++)
            if(compress[i] != "" && compress[j] != "")
            {
                size_t size = std::min(compress[i].size(), compress[j].size());

                CHECK(compress[i].substr(0, size) != compress[j].substr(0, size));
            }
};

TEST_CASE("Test prefix code with different weights") 
{
    std::vector<int> cnt(256);
    std::mt19937 rnd(1337);

    for(size_t i = 0; i < 256; i++)
    {
        size_t mod = (1e5) / ((i + 2) * (i + 2));
        cnt[i] = rnd() % mod;
    }

    Tree tr(cnt);
    auto compress = tr.compress();

    for(size_t i = 0; i < compress.size(); i++)
        for(size_t j = i + 1; j < compress.size(); j++)
            if(compress[i] != "" && compress[j] != "")
            {
                size_t size = std::min(compress[i].size(), compress[j].size());

                CHECK(compress[i].substr(0, size) != compress[j].substr(0, size));
            }
};

TEST_CASE("Tree dump test") 
{
    std::vector<int> cnt(256);
    cnt[100] = 1000;
    cnt[50]  = 100;
    cnt[25]  = 10;
    cnt[12]  = 1;

    Tree tr(cnt);

    std::stringstream is;

    tr.dump(is);
    HuffmanArchiver h;

    auto tree_in_file = h.get_tree_for_test(is);

    CHECK(tr.compress() == tree_in_file);
};

TEST_CASE("Test TreeWalker") 
{
    std::vector<int> cnt(256);
    cnt['a'] = 1000;
    cnt['b'] =  100;
    cnt['c'] =   10;
    cnt['d'] =    1;

    Tree tr(cnt);

    std::stringstream is;

    tr.dump(is);
    HuffmanArchiver archiver;

    auto tree = archiver.get_HuffmanTree_for_test(is);

    auto walker = tree.get_walker();

    std::string way = "101001000010011";

    std::stringstream os;

    size_t message_size = 0;
    for(const auto &bit : way)
        if(bit == '0')
            walker.go_left(os, message_size);
        else
            walker.go_right(os, message_size);

    CHECK(message_size == 7);
    CHECK(os.str() == "abcdbca");
};
