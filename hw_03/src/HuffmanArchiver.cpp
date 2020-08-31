#include "HuffmanArchiver.h"
#include "HuffmanTree.h"
#include "Resulter.h"
#include "BitWriter.h"
#include "BitReader.h"

#include <iostream>
#include <vector>

#include <iostream>
#include <cassert>
#include <tuple>

using std::cout;
using std::endl;

std::vector<int> get_rates(std::istream &is, size_t &input_size)
{
    std::vector<int> rates(256);

    uint8_t data;
    for(; is; )
    {
        is.read((char*)&data, sizeof(data));
        if(is)
        {
            rates[data]++;
            input_size++;
        }
    }

    is.clear();
    is.seekg(0);

    return rates;
}

Resulter HuffmanArchiver::compress(std::istream &is, std::ostream &os)
{
    if(!is)
    {
        return Resulter();
    }

    size_t input_size = 0;
    size_t table_size = 0;
    size_t compressed = 0;
    
    std::vector<int> rates(std::move(get_rates(is, input_size)));

    table_size += sizeof(input_size);
    os.write((char*)&input_size, sizeof(input_size));

    tr_ = Tree(rates);
    table_size += tr_.dump(os);

    BitWriter writer;

    uint8_t data;

    for(; is; )
    {
        is.read((char*)&data, sizeof(data));

        if(is)
        {
            for(const auto &bit : tr_.compress()[data])
                compressed += writer.write(bit - '0', os);
        }
    }

    compressed += writer.dump(os);

    return Resulter(input_size, compressed, table_size);
}


Resulter HuffmanArchiver::extract(std::istream &is, std::ostream &os)
{
    if(!is)
    {
        return Resulter();
    }

    HuffmanTree tree;

    size_t file_size = 0;
    size_t table_size = 0;
    size_t compressed = 0;

    is.read((char*)&file_size, sizeof(file_size));
    table_size += sizeof(file_size);

    uint16_t alphabet_size;

    is.read((char*)&alphabet_size, sizeof(alphabet_size));
    table_size += sizeof(alphabet_size);

    BitReader reader;

    for(int i = 0; i < alphabet_size; i++)
    {
        uint8_t ch;
        is.read((char*)&ch, sizeof(ch));
        table_size += sizeof(ch);

        uint16_t bit_count;
        is.read((char*)&bit_count, sizeof(bit_count));
        table_size += sizeof(bit_count);

        std::string binary_string;

        table_size += reader.read_to_string(is, bit_count, binary_string);
        tree.add_letter(binary_string, ch);
    }

    size_t output_size = 0;

    auto walker = tree.get_walker();
    for(; is; )
    {
        uint8_t ch;
        is.read((char*)&ch, sizeof(ch));
        compressed++;

        for(int k = 0; output_size < file_size && k < 8; k++)
        {
            if(!(ch & (1 << k)))
            {
                walker.go_left(os, output_size);
            }
            else
            {
                walker.go_right(os, output_size);
            }
        }

    }
    compressed--;

    return Resulter(compressed, file_size, table_size);
}


std::vector<std::string> HuffmanArchiver::get_tree_for_test(std::istream &is)
{
    std::vector<std::string> tree(256);

    uint16_t alphabet_size;

    is.read((char*)&alphabet_size, sizeof(alphabet_size));

    BitReader reader;

    for(int i = 0; i < alphabet_size; i++)
    {
        uint8_t ch;
        is.read((char*)&ch, sizeof(ch));

        uint16_t bit_count;
        is.read((char*)&bit_count, sizeof(bit_count));

        std::string binary_string;

        reader.read_to_string(is, bit_count, binary_string);
        tree[ch] = binary_string;
    }

    return tree;
}

HuffmanTree HuffmanArchiver::get_HuffmanTree_for_test(std::istream &is)
{
    HuffmanTree tree;

    uint16_t alphabet_size;

    is.read((char*)&alphabet_size, sizeof(alphabet_size));

    BitReader reader;

    for(int i = 0; i < alphabet_size; i++)
    {
        uint8_t ch;
        is.read((char*)&ch, sizeof(ch));

        uint16_t bit_count;
        is.read((char*)&bit_count, sizeof(bit_count));

        std::string binary_string;

        reader.read_to_string(is, bit_count, binary_string);
        tree.add_letter(binary_string, ch);
    }
    return tree;
}
