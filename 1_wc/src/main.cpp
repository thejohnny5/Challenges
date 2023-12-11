#include <iostream>
#include <string>
#include "wc.hpp"
#include "../../parsing_util/src/Parser.hpp"

int main (int argc, char *argv[]) {
    
    ArgumentParser parser = ArgumentParser("ccwc", "Counts the Lines, Chars, and Words in text");
    parser.addArgument("word", 'w', "", false, "Returns word count in file");
    parser.addArgument("line", 'l', "", false, "Returns line count in file");
    parser.addArgument("char", 'c', "", false, "Returns character count in file");

    std::shared_ptr<FH::FF> myFile;

    if (parser.isUsed("word")){
        myFile = std::make_shared<FH::FF>(parser.getDefault(), FH::ffmode::DEFAULT);
        std::cout << myFile->getWords() << " " << parser.getDefault() << std::endl;
        return 0;
    } else if (parser.isUsed("line")){
        myFile = std::make_shared<FH::FF>(parser.getDefault(), FH::ffmode::BINARY);
        std::cout << myFile->getLines() << " " << parser.getDefault() << std::endl;
        return 0;
    } else if (parser.isUsed("character")){
        myFile = std::make_shared<FH::FF>(parser.getDefault(), FH::ffmode::BINARY);
        std::cout << myFile->charCount() << " " << parser.getDefault() << std::endl;
        return 0; 
    } else {
        myFile = std::make_shared<FH::FF>(parser.getDefault(), FH::ffmode::BINARY);
        int chars = myFile->charCount();
        int lines = myFile->getLines();
        myFile = std::make_shared<FH::FF>(parser.getDefault(), FH::ffmode::DEFAULT);
        int words = myFile->getWords();
        std::cout << lines << " " << words << " " << chars << " " << parser.getDefault() << std::endl;

    }

    return 0;
}
