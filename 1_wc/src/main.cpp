#include <iostream>
#include <string>
#include "wc.h"

void usage(){
    std::cout << "Usage: ccwc [OPTION] <File>" << std::endl;
    std::cout << "\tOption" <<std::endl;
    std::cout << "\t-c\tNumber of characters in file" << std::endl;
    std::cout << "\t-l\tNumber of lines in file" << std::endl;
    std::cout << "\t-w\tNumber of words in file" << std::endl;
    std::cout << std::endl << "If no options sepecified, prints 'line count' 'word count' 'char count'" << std::endl; 
}

int main (int argc, char *argv[]) {
    
    // Check numbre of parameters
    if (argc < 2 || argc>3){
        usage();
        return 1;
    }
    
    // If run like 'wcww <file>'
    // print out "lines words chars"
    FH::FF* myFile;
    if (argc == 2){
        myFile = new FH::FF(argv[1], FH::ffmode::BINARY);
        int chars = myFile->charCount();
        int lines = myFile->getLines();
        myFile->close();
        myFile->open(argv[1], FH::ffmode::DEFAULT);
        int words = myFile->getWords();
        delete myFile;
        std::cout << lines << " " << words << " " << chars << " " << argv[1] << std::endl;
        return 0;
    }

    switch (argv[1][1]) {
        case 'c':{
            myFile = new FH::FF(argv[2], FH::ffmode::BINARY);
            uint64_t count = myFile->charCount();
            std::cout << count << " " << argv[2] << std::endl;
            break;
        }
        case 'l':{
            myFile = new FH::FF(argv[2], FH::ffmode::BINARY);
            uint16_t count = myFile->getLines();
            std::cout << count << " " << argv[2] << std::endl;
            break;
        }
        case 'w':{
            myFile = new FH::FF(argv[2], FH::ffmode::DEFAULT);
            uint32_t count = myFile->getWords();
            std::cout << count << " " << argv[2] << std::endl;
            break;
        }
        case 'h':{
            usage();
            return 0;
        }
        default:{
            std::cerr << "Couldn't read argv: " << argv[1] << std::endl;
            usage();
            return 1;
        }
    }
    delete myFile;

    return 0;
}
