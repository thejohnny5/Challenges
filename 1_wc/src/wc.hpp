#include <iostream>
#include <fstream>
#include <string>

namespace FH {

   
struct Counts {
    uint32_t lines;
    uint32_t words;
    uint32_t characters;
};
Counts getWordLineCharCounts(std::istream& ff, bool countLines, bool countWords, bool countChars);
}
