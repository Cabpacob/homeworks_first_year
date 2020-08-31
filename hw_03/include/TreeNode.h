#pragma once
#include <memory>
#include <set>
#include <iostream>
#include <vector>
#include <algorithm>

class TreeNode
{
public:

	TreeNode(const TreeNode &l, const TreeNode &r) :  count_(l.count_ + r.count_) 
    {
        for(auto i : l.bytes())
            bytes_.push_back(i);
        for(auto i : r.bytes())
            bytes_.push_back(i);
    };

    TreeNode(const uint8_t chr, const int32_t cnt) : count_(cnt)
    {
        bytes_.push_back(chr);
    };

    const std::vector<uint8_t> &bytes() const ;

    bool operator<(const TreeNode &other) const ;
private:
	std::vector<uint8_t> bytes_;
	int32_t count_;
};
