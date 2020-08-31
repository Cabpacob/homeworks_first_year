#include "Tree.h"
#include "TreeNode.h"
#include "BitWriter.h"

#include <set>
#include <algorithm>

Tree::Tree(const std::vector<int> &counts) : compress_(256)
{
    std::multiset<TreeNode> roots;
    for(int i = 0; i < 256; i++)
        if(counts[i])
            roots.emplace(i, counts[i]);

    if(roots.size() == 1)
    {
        compress_[roots.begin()->bytes()[0]] = "0";
    }

    for(; roots.size() > 1;)
    {
        const TreeNode left_subtree(*roots.begin());
        roots.erase(roots.begin());
        const TreeNode right_subtree(*roots.begin());
        roots.erase(roots.begin());

        for(const auto &byte : left_subtree.bytes())
            compress_[byte] += '0';

        for(const auto &byte : right_subtree.bytes())
            compress_[byte] += '1';

        roots.emplace(left_subtree, right_subtree);
    }

    for(int i = 0; i < 256; i++)
        if(compress_[i].size())
        {
            std::reverse(compress_[i].begin(), compress_[i].end());
        }
}

size_t Tree::dump(std::ostream &os)
{
    size_t table_size = 0;

    uint16_t alphabet_size = 0;
    for(int i = 0; i < 256; i++)
        if(compress_[i] != "")
            alphabet_size++;

    os.write((char*)&alphabet_size, sizeof(alphabet_size));
    table_size += sizeof(alphabet_size);

    BitWriter writer;

    for(int i = 0; i < 256; i++)
        if(compress_[i] != "")
        {
            uint8_t ch = i;
            os.write((char*)&ch, sizeof(ch));
            table_size++;

            uint16_t code_size = compress_[i].size();
            os.write((char*)&code_size, sizeof(code_size));
            table_size += sizeof(code_size);

            for(const auto &bit : compress_[ch])
                table_size += writer.write(bit - '0', os);

            table_size += writer.dump(os);

        }
    return table_size;
}

const std::vector<std::string> &Tree::compress() const
{
    return compress_;
}
