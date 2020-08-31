#include "TreeNode.h"

bool TreeNode::operator<(const TreeNode &other) const
{
    return count_ < other.count_;
}

const std::vector<uint8_t> &TreeNode::bytes() const
{
    return bytes_;
}
