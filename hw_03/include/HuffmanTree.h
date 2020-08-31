
#pragma once
#include "HuffmanNode.h"
#include <memory>
#include <string>
#include <iostream>

class HuffmanTree
{
private:
    class TreeWalker
    {
    public:
        TreeWalker(std::shared_ptr<HuffmanNode> &root) : node_(root), default_(root) {};
        void go_left(std::ostream &os, size_t &file_size);
        void go_right(std::ostream &os, size_t &file_size);

    private:
        std::shared_ptr<HuffmanNode> node_, default_;
    };
public:
    HuffmanTree() : root_(std::make_shared<HuffmanNode>()) {};
    void add_letter(const std::string &code, char letter);

    TreeWalker get_walker();
private:
    
    std::shared_ptr<HuffmanNode> root_;
};
