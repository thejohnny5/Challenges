#include <iostream>
#include <string>
#include <sstream>
#include "wc.hpp"

FH::Counts FH::getWordLineCharCounts(std::istream& ff, bool countLines, bool countWords, bool countChars) {
    Counts counts = {0, 0, 0};
    std::string line;

    while (std::getline(ff, line)) {
        if (countLines) {
            ++counts.lines;
        }
        if (countChars) {
            counts.characters += line.length() + 1;
        }
        if (countWords) {
            std::istringstream lineStream(line);
            std::string word;
            while (lineStream >> word) {
                ++counts.words;
            }
        }
    }

    return counts;
}
