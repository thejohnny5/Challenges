#include <string>
#include <fstream>
#include <memory>
#include <sstream>

namespace HT {

// class FileUtil {
// public:
//     std::fstream openFile(std::string name, const int streamType);
//     std::string readChunk(std::fstream file, const size_t chunkSize);
//     void writeChunk(std::fstream outFile, std::string processedChunk);
// };

struct HuffmanNode {
    uint8_t character;
    int frequency;
    std::shared_ptr<HuffmanNode> left, right;
    HuffmanNode(uint8_t c, int f, std::shared_ptr<HuffmanNode> l = nullptr, std::shared_ptr<HuffmanNode> r = nullptr) :
    character(c), frequency(f), left(l), right(r) {};
};


class Compare {
public:
    bool operator()(const std::shared_ptr<HuffmanNode>& v1, const std::shared_ptr<HuffmanNode>& v2) const {
        return v1->frequency > v2->frequency;
    }
};



class HuffmanTree {
    private:
        std::shared_ptr<HuffmanNode> root;
        void buildLookUpTable(std::shared_ptr<HuffmanNode> node, std::unordered_map<uint8_t, std::string> &lookupTable, std::string code);
        void internSerialize(std::shared_ptr<HuffmanNode> node, std::string &serializedString);
        void internDeserialize(std::shared_ptr<HuffmanNode> &node, std::stringstream &stringStream);
    public:
    // Takes root and serializes huffman tree
    std::string Serialize();

    // Builds a huffman tree from the header section and assigns to root
    size_t Deserialize(std::string header);

    // Takes count vector and builds a tree from this, assigning root to root 
    void BuildFromFrequencyMap(std::vector<uint64_t> frequency_map); 

    std::unordered_map<uint8_t, std::string> MakeLookUpTable();

    std::vector<bool> Encode(const std::unordered_map<uint8_t, std::string> &lookupTable, const std::string &messageToEncode);

    std::string Decode(const std::vector<bool> &bitMessage, size_t size);
};

enum class ASCIItype {
    T128 = 128,
    T256 = 256
};

std::vector<bool> StringToBit(std::string s);

// class Chunker{
// private:
//     std::ifstream file;
//     size_t chunkSize;
// public:
//     Chunker(std::ifstream file, size_t chunkSize);
//     ~Chunker();
//     bool eof();
//     void resize(size_t chunksize);
//     std::vector<char> getChunk();
//     void writeChunk(std::string text);
//     void clear();
//     void seekg();
// };

class FrequencyBuilder
{
private:
    std::vector<uint64_t> frequency_map;
    // void build_frequency_map(std::vector<char> buffer);
    void build_frequency_map(std::string text);
public:
    // std::vector<uint64_t> build_frequency_map_from_file(FileUtil file, ASCIItype size);
    std::vector<uint64_t> buildAndGetFrequencyMap(std::string text, ASCIItype size);
};
void writeHeader(const std::string& header, const size_t messageSize, const std::string& filename);
void writeOut(const std::vector<bool>& encodedBits, const std::string& filename);
void EncodeMessage(const std::string& fileNameIn, const std::string& fileNameOut, const std::string& headerOut);
void DecodeMessage(const std::string& fileNameIn, const std::string& fileNameOut, const std::string& headerIn);
}
