#include "HuffmanTree.hpp"
#include <queue>
#include <iostream>
// void HT::FrequencyBuilder::build_frequency_map(std::vector<char> text)
// {
//     for (auto &c: text){
//         frequency_map[c]++;
//     }
// }

// std::vector<uint64_t> HT::FrequencyBuilder::build_frequency_map_from_file(FileUtil file, ASCIItype size, size_t chunkSize)
// {
//     frequency_map.resize((int)size, 0);
//     while (!file.eof()){
//         std::vector<char> buffer = file.readChunk();
//         build_frequency_map(buffer);
//     }

//     return frequency_map;
// }


// #include <fstream>
// #include <string>
// #include <vector>

// std::vector<char> readChunk(std::ifstream& file, std::size_t chunkSize) {
//     std::vector<char> buffer(chunkSize);
//     if (file.read(buffer.data(), chunkSize)) {
//         // Resize the buffer to the actual number of bytes read
//         buffer.resize(file.gcount());
//     } else {
//         // Handle the end of the file or a read error
//         buffer.clear();
//     }
//     return buffer;
// }

std::vector<bool> HT::StringToBit(std::string s){
        std::vector<bool> bitVector;
    bitVector.reserve(s.size() * 8);

    for (uint8_t ch : s) {
        for (int i = 7; i >= 0; --i) {
            bitVector.push_back((ch >> i) & 1);
        }
    }

    return bitVector;
}

// Builds a frequency map from the text and returns it
std::vector<uint64_t> HT::FrequencyBuilder::buildAndGetFrequencyMap(std::string text, ASCIItype size){
    frequency_map.resize((int)size, 0);
    build_frequency_map(text);
    return frequency_map;
}

// This should work
void HT::FrequencyBuilder::build_frequency_map(std::string text)
{
    for (char &c:text){
        frequency_map[static_cast<uint8_t>(c)]++;
    }
}

void HT::HuffmanTree::BuildFromFrequencyMap(std::vector<uint64_t> frequency_map)
{
    std::priority_queue<std::shared_ptr<HT::HuffmanNode>, std::vector<std::shared_ptr<HT::HuffmanNode>>, HT::Compare> q;
    
    for (int i=0; i<frequency_map.size(); i++){
        if (frequency_map[i]>0){
            // std::cout << static_cast<char>(i) << ": " << frequency_map[i] << std::endl;
            q.push(std::make_shared<HT::HuffmanNode>(static_cast<uint8_t>(i), frequency_map[i]));
        }
    }

    while (q.size()>1){
        auto n1= q.top();
        q.pop();
        auto n2 = q.top();
        q.pop();
        auto comb = std::make_shared<HT::HuffmanNode>('\0', n1->frequency + n2->frequency, n1, n2);
        q.push(comb);
    }
    // std::cout << "Q Top: " << q.top()->frequency << std::endl;
    root = q.size()==1 ? q.top() : nullptr;
}

std::unordered_map<uint8_t, std::string> HT::HuffmanTree::MakeLookUpTable()
{
    std::unordered_map<uint8_t, std::string> lookupTable;
    HT::HuffmanTree::buildLookUpTable(root, lookupTable, "");
    return lookupTable; 
}

void HT::HuffmanTree::buildLookUpTable(std::shared_ptr<HT::HuffmanNode> root, std::unordered_map<uint8_t, std::string>& lookupTable, std::string code) {
    if (!root) {
        return;
    }

    // When a leaf node is reached, add the symbol and its code to the lookup table
    if (!root.get()->left && !root.get()->right) {
        lookupTable[root->character] = code;
        return;
    }

    // Traverse left
    HT::HuffmanTree::buildLookUpTable(root->left, lookupTable, code + "0");
    // Traverse right
    HT::HuffmanTree::buildLookUpTable(root->right, lookupTable, code + "1");
}

std::string HT::HuffmanTree::Serialize(){
    std::string serializedString = "";
   
    HT::HuffmanTree::internSerialize(root, serializedString);

    return serializedString;
};


void HT::HuffmanTree::internSerialize(std::shared_ptr<HT::HuffmanNode> node, std::string &serializedString)
{
     if (!node){
        serializedString += "0:-1 ";
        return;
    }
    serializedString += std::to_string(node->character) + ":" + std::to_string(node->frequency) + " ";
    HT::HuffmanTree::internSerialize(node->left, serializedString);
    HT::HuffmanTree::internSerialize(node->right, serializedString);
}

size_t HT::HuffmanTree::Deserialize(std::string string){
    // std::cout << string << std::endl;
    std::stringstream stringStream(string);
    size_t size;
    stringStream >> size;
    HT::HuffmanTree::internDeserialize(root, stringStream);
    return size;
}

void HT::HuffmanTree::internDeserialize(std::shared_ptr<HT::HuffmanNode> &node, std::stringstream &stringStream){
        std::string charPart, freqPart;
    getline(stringStream, charPart, ':');
    getline(stringStream, freqPart, ' ');

    // Convert string parts to integer
    int character = std::stoi(charPart);
    int frequency = std::stoi(freqPart);

    // std::cout << "Char: " << character << "Freq: " << frequency << std::endl;

    if (character==0 && frequency == -1){
        return;
    }

    node = std::make_shared<HT::HuffmanNode>(static_cast<uint8_t>(character), frequency);
    HT::HuffmanTree::internDeserialize(node->left, stringStream);
    HT::HuffmanTree::internDeserialize(node->right, stringStream);

}

std::vector<bool> HT::HuffmanTree::Encode(const std::unordered_map<uint8_t, std::string> &lookupTable, const std::string &messageToEncode)
{
    // Use lookup table to encode bit string
    std::vector<bool> encodedBits;
    int i = 0;
    for (char ch: messageToEncode){
        auto it = lookupTable.find(static_cast<uint8_t>(ch));
        i++;
        if (it != lookupTable.end()){
            // apppend huffman code to encoded message
            for (char bit: it->second){
                encodedBits.push_back(bit == '1');
            }
        } else {
            // Handle error for char not in lookup table
            std::cerr << "Character '" << static_cast<uint8_t>(ch) << "' not found in lookup table" << "Position: " << (i-1) << std::endl;
        }
    }
    return encodedBits;
}

std::string HT::HuffmanTree::Decode(const std::vector<bool> &bitMessage, size_t size) {
    std::string message;
    auto curr = root;
    int i=0;
    for (bool bit : bitMessage) {
        if (++i>size) break;
        if (!curr) {
            // Handle error: current node is null, which shouldn't happen in a valid tree traversal
            std::cerr << "Current node is null ERROR" << std::endl;
            exit(1);
        }

        // Traverse the Huffman tree: left for 0, right for 1
        curr = bit ? curr->right : curr->left;

        // Check if the current node is a leaf node
        if (!curr->left && !curr->right) {
            message += curr->character;
            curr = root; // Reset to start for the next character
        }
    }

    // Check if the last node was correctly processed
    if (curr != root) {
        // Handle the case where the bit sequence doesn't end at a leaf node
        std::cerr << "Bit doesn't end at leaf node" << std::endl;
        exit(1);
    }

    return message;
}


void HT::writeHeader(const std::string& header, const size_t messageSize, const std::string& filename) {
    std::ofstream fh(filename, std::ios::out | std::ios::binary);
    if (!fh) {
        std::cerr << "Failed to open file for header: " << filename << std::endl;
        return;
    }
    fh << messageSize << " ";
    fh << header;
    fh.close();
}

void HT::writeOut(const std::vector<bool>& encodedBits, const std::string& filename) {
    std::ofstream fout(filename, std::ios::out | std::ios::binary);
    if (!fout) {
        std::cerr << "Failed to open file for output: " << filename << std::endl;
        return;
    }

    char currentByte = 0;
    int bitCount = 0;

    for (bool bit : encodedBits) {
        // Set the bit in the current byte
        if (bit) {
            currentByte |= (1 << (7 - bitCount));
        }

        bitCount++;

        // Write the byte if it's full
        if (bitCount == 8) {
            fout.write(&currentByte, 1);
            currentByte = 0;
            bitCount = 0;
        }
    }

    // Write any remaining bits (if the total number of bits is not a multiple of 8)
    if (bitCount > 0) {
        fout.write(&currentByte, 1);
    }

    fout.close();
}

void HT::EncodeMessage(const std::string& fileNameIn, const std::string& fileNameOut, const std::string& headerOut) {
    // Read input file
    std::ifstream fin(fileNameIn, std::ios::in | std::ios::binary);
    if (!fin) {
        std::cerr << "Failed to open input file: " << fileNameIn << std::endl;
        return;
    }
    std::string s((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();

    // std::cout << s.substr(0, 20) << std::endl;
    // Generate frequency map
    HT::FrequencyBuilder bd;
    std::vector<uint64_t> freq_map = bd.buildAndGetFrequencyMap(s, HT::ASCIItype::T256);

    // std::cout << "X: "<< freq_map['X'] << std::endl;
     

    // Build Huffman tree
    HT::HuffmanTree ht;
    ht.BuildFromFrequencyMap(freq_map);
    auto lookupTable = ht.MakeLookUpTable();

    // for (const auto& pair : lookupTable) {
    //     std::cout << pair.first << ": " << pair.second << std::endl;
    // }

    // Encode the message
    std::vector<bool> encodedMessage = ht.Encode(lookupTable, s);
    // std::cout << "Done with encode" << std::endl;
    // // Write header and encoded message to output files
    HT::writeHeader(ht.Serialize(), encodedMessage.size(), headerOut);
    // std::cout << "Done with Serialize" << std::endl;
    HT::writeOut(encodedMessage, fileNameOut);
}

void HT::DecodeMessage(const std::string& fileNameIn, const std::string& fileNameOut, const std::string& headerIn)
{
   std::ifstream fin(fileNameIn, std::ios::in | std::ios::binary);
    if (!fin) {
        std::cerr << "Failed to open input file: " << fileNameIn << std::endl;
        return;
    }
    std::string s((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();

    std::ifstream header(headerIn, std::ios::in | std::ios::binary);
    if (!header) {
        std::cerr << "Failed to open header file: " << headerIn << std::endl;
        return;
    }
    std::string serializedString((std::istreambuf_iterator<char>(header)), std::istreambuf_iterator<char>());
    // std::cout << "Htree" << std::endl;
    HT::HuffmanTree ht;
    size_t fileSize = ht.Deserialize(serializedString);
    // std::cout << "Deserialized" << std::endl;
    std::string message = ht.Decode(HT::StringToBit(s), fileSize);
    std::cout << message;

}
// void EncodeMessage(std::string fileNameIn, std::string fileNameOut, std::string headerOut)
// {
//     std::fstream fin;//open file
//     std::string s; // = read file from 
//     // generate freq map
//     HT::FrequencyBuilder bd;
//     std::vector<uint64_t> freq_map = bd.buildAndGetFrequencyMap(s, HT::ASCIItype::T256);

//     // Tree
//     HT::HuffmanTree ht;
//     ht.BuildFromFrequencyMap(freq_map);

//     auto lookupTable = ht.MakeLookUpTable();

//     std::string encodedMessage = ht.Encode(lookupTable, s);

//     std::fstream fh; // file made from hederOut
//     writeHeader(ht.Serialze(), fh);

//     std::fstream fout; // made from fileNameOut
//     writeOut(encodedMessage, fout);

// }


// class BitStream {
// private:
//     std::vector<bool> bits;
//     int currPos;
//     bool end;

// public:
//     BitStream(const std::vector<bool>& b) : bits(b), currPos(0), end(false) {}

//     bool read() {
//         if (currPos >= bits.size()) {
//             throw std::out_of_range("Attempted to access bit outside of range");
//         }
//         if (currPos == bits.size() - 1) end = true;
//         return bits[currPos++];
//     }

//     void reset() {
//         currPos = 0;
//         end = false;
//     }

//     bool isEnd() const { return end; }
// };
