#include "HuffmanNode.h"

std::shared_ptr<HuffmanNode> &HuffmanNode::left()
{
    return l_;
}

std::shared_ptr<HuffmanNode> &HuffmanNode::right()
{
    return r_;
}

char HuffmanNode::letter()
{
    return ch_;
}

bool HuffmanNode::terminal()
{
    return !l_ && !r_;
}
