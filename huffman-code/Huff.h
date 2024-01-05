#ifndef _HUFF_H
#define _HUFF_H

#include <string>
#include <unordered_map>

class HuffNode {
    public:
        char c;
        HuffNode *left;
        HuffNode *right;
        HuffNode(char c) : c(c), left(nullptr), right(nullptr) {}                                                    // constructor
        HuffNode(char c, HuffNode *l, HuffNode *r) : c(c), left(l), right(l) {}       // constructor with pointers
};

void huff_encode(std::string content, std::string filename);
std::string huff_decode(std::string filename);

#endif