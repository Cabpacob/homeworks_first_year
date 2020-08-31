#include "HuffmanTree.h"
#include "HuffmanNode.h"

#include <cassert>
#include <iostream>

void HuffmanTree::add_letter(const std::string &code, char letter)
{
    std::shared_ptr<HuffmanNode> node = root_;
    for(const auto &i : code)
        if(i == '0')
        {
            if(!node->left())
                node->l_ = std::make_shared<HuffmanNode>();
            node = node->left();
        }
        else
        {
           if(!node->right())
                node->r_ = std::make_shared<HuffmanNode>();
            node = node->right(); 
        }

    node->ch_ = letter;
}

HuffmanTree::TreeWalker HuffmanTree::get_walker()
{
    return TreeWalker(root_);
}

void HuffmanTree::TreeWalker::go_left(std::ostream &os, size_t &file_size)
{
    node_ = node_->left();
    
    if(node_->terminal())
    {
        os << node_->letter();
        file_size++;
        node_ = default_;
    }
}

void HuffmanTree::TreeWalker::go_right(std::ostream &os, size_t &file_size)
{
    node_ = node_->right();

    if(node_->terminal())
    {
        os << node_->letter();
        file_size++;
        node_ = default_;
    }
}
