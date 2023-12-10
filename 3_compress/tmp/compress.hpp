#include <string>
#include <fstream>

struct HuffmanNode {
    int weight;
    char symbol;
    std::shared_ptr<HuffmanNode> left, right;
    HuffmanNode(int w, char s, std::shared_ptr<HuffmanNode> left = nullptr, std::shared_ptr<HuffmanNode> right = nullptr) 
        : weight(w), symbol(s), left(left), right(right) {}
};

class Compressor{
public:
std::fstream file;
std::vector<int> freq;
    Compressor(std::string filename);
    ~Compressor();
    void buildFrequencies();   
    std::shared_ptr<HuffmanNode> buildNodes();
};

void buildLookupTable(std::shared_ptr<HuffmanNode> root, std::unordered_map<char, std::string>& lookupTable, std::string code = "");