#include <iostream>
#include <string>
#include "wc.hpp"
#include "../../parsing_util/src/Parser.hpp"

int main (int argc, const char *argv[]) {
    ArgumentParser parser = ArgumentParser("ccwc", "Counts the Lines, Chars, and Words in text");
    parser.addArgument("word", 'w', "", false, "Returns word count in file");
    parser.addArgument("line", 'l', "", false, "Returns line count in file");
    parser.addArgument("character", 'c', "", false, "Returns character count in file");
    parser.parse(argc, argv);
    std::istream* ff = nullptr;  // Use a pointer to std::istream
    std::ifstream fileStream;

    if (parser.getDefaultInputSource() == InputSource::Stdin) {
        ff = &std::cin;  // Point to std::cin for stdin
    } else {
        std::string filename = parser.getDefault();
        fileStream.open(filename);
        if (!fileStream) {
            std::cerr << "Could not open file: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        ff = &fileStream;  // Point to the file stream for file input
    }
    FH::Counts counts;
    if (!parser.isUsed("line") && !parser.isUsed("word") && !parser.isUsed("character")) counts = FH::getWordLineCharCounts(*ff, true, true, true);
    else counts = FH::getWordLineCharCounts(*ff, parser.isUsed("line"), parser.isUsed("word"), parser.isUsed("character"));

    if (parser.isUsed("word")){
        std::cout << counts.words << " " << parser.getDefault() << std::endl;
        return 0;
    } else if (parser.isUsed("line")){
        std::cout << counts.lines << " " << parser.getDefault() << std::endl;
        return 0;
    } else if (parser.isUsed("character")){
        std::cout << counts.characters << " " << parser.getDefault() << std::endl;
        return 0; 
    } else {
        std::cout << counts.lines << " " << counts.words << " " << counts.characters << " " << parser.getDefault() << std::endl;

    }

    return 0;
}
