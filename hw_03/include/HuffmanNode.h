#pragma once
#include <memory>

class HuffmanTree;

class HuffmanNode
{
public:
    HuffmanNode() : l_(nullptr), r_(nullptr), ch_(0) {}; 
    HuffmanNode(std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r, char c = 0) : l_(l), r_(r), ch_(c) {};
    std::shared_ptr<HuffmanNode> &left();
    std::shared_ptr<HuffmanNode> &right();
    char letter();

    bool terminal();
    friend HuffmanTree;
private:
    std::shared_ptr<HuffmanNode> l_, r_; // left - 0, right - 1
    char ch_;
};