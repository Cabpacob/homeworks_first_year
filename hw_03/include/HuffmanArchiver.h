
#pragma once

#include "Tree.h"
#include "Resulter.h"
#include "HuffmanTree.h"

#include <iostream>
#include <vector>


class HuffmanArchiver
{
public:
	Resulter compress(std::istream &is, std::ostream &os);
	Resulter extract(std::istream &is, std::ostream &os);

    std::vector<std::string> get_tree_for_test(std::istream &is);
    HuffmanTree get_HuffmanTree_for_test(std::istream &is);

private:
    Tree tr_;
};