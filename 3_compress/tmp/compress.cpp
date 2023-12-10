#include "compress.hpp"
#include <string>
#include <iostream>
#include <queue>

class Compare {
public:
    bool operator()(const std::shared_ptr<HuffmanNode>& v1, const std::shared_ptr<HuffmanNode>& v2) const {
        return v1->weight > v2->weight;
    }
};

Compressor::Compressor(std::string filename)
{
    file.open(filename);
    if (!file.good()){
        std::cerr << "Error opening file" << std::endl;
    }
}
Compressor::~Compressor()
{
    file.close();
}
void Compressor::buildFrequencies()
{
    char c;
    freq.resize(256, 0);
    while (file.good()){
        c = file.get();
        freq[c]++;
    }
    file.clear();
};

std::shared_ptr<HuffmanNode> Compressor::buildNodes()
{
    std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, Compare> q;
    // Convert all vector into HuffmanNodes
    for (int i=0; i<freq.size(); i++){
        if (freq[i] > 0) {
            q.push(std::make_shared<HuffmanNode>(freq[i], static_cast<char>(i)));
        }
    }

    while (q.size()>1){
        auto n1 = q.top();
        q.pop();
        auto n2 = q.top();
        q.pop();
        auto comb = std::make_shared<HuffmanNode>(n1->weight + n2->weight, '\0', n1, n2);
        q.push(comb);
    }
    return q.size()==1 ? q.top() : nullptr;
}

void buildLookupTable(std::shared_ptr<HuffmanNode> root, std::unordered_map<char, std::string>& lookupTable, std::string code) {
    if (!root) {
        return;
    }

    // When a leaf node is reached, add the symbol and its code to the lookup table
    if (!root.get()->left && !root.get()->right) {
        lookupTable[root->symbol] = code;
        return;
    }

    // Traverse left
    buildLookupTable(root->left, lookupTable, code + "0");
    // Traverse right
    buildLookupTable(root->right, lookupTable, code + "1");
}

