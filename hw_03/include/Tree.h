#pragma once
#include <vector>
#include <iostream>
#include <string>

class Tree
{
public:
    Tree() : compress_(256) {}; 
    Tree(const std::vector<int> &counts);

    size_t dump(std::ostream &os);
    const std::vector<std::string> &compress() const;
private:
    std::vector<std::string> compress_;
};
