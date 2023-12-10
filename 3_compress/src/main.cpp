#include <iostream>
#include <string>
#include "HuffmanTree.hpp"
#include <memory>
void usage(){
    std::cout << "Usage: json_parse <File>" << std::endl;
}

int main (int argc, char *argv[]) {
    
    // Check numbre of parameters
    if (argc < 2 || argc>3){
        usage();
        return 1;
    }
    if (argc == 3){
        HT::DecodeMessage("testout.txt", "filler", "testheaders.txt");
        return 0;
    } 
    // If run like 'wcww <file>'
    // print out "lines words chars"
    if (argc == 2){
        HT::EncodeMessage(argv[1], "testout.txt", "testheaders.txt");
//         auto cp = std::make_unique<Compressor>(argv[1]);
//         cp->buildFrequencies();
//         std::shared_ptr<HuffmanNode> root = cp->buildNodes();
//         std::unordered_map<char, std::string> lookupTable;
//         buildLookupTable(root, lookupTable);
//  for (const auto& pair : lookupTable) {
//         std::cout << pair.first << ": " << pair.second << std::endl;
//     }
        return 0;
    }
    

    return 0;
}
