#include "wc.hpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

FH::FF::FF(std::string file, FH::ffmode mode){
    open(file, mode);
}

FH::FF::~FF(){
    ff.close();
}

int FH::FF::charCount(){
    // Read in file character by character
    //
    if (!ff.is_open()) return -1;
    ff.seekg(0, std::ios::end);
    std::streampos length = ff.tellg();
    ff.clear();
    ff.seekg(0, std::ios::beg);
    return static_cast<int>(length);
}

uint16_t FH::FF::getLines(){
    if (!ff.is_open()) return 0;
    // Should be binary stream 
    char c;
    char nl = '\n';
    uint64_t lines = 0;
    // while ff, exclusive or char with carriage return 
    while (ff){
        c = ff.get();
        if ((c^nl)== 0) lines++;
    }
    // if !0 lines++
    ff.clear();
    ff.seekg(0, std::ios::beg);
    return lines;
}

// Function to mimic wc -c
uint32_t FH::FF::getWords(){
    // return 0 if f is not open. Will change implementation later
    if (!ff.is_open()) return 0;
    char c = ' ';
    // char nl = ' ';
    uint32_t words = 0;
    while (ff){
        // moves through all white spaces and returns
        while (ff && ((c^' ')==0 || (c^'\n')==0 || (c^'\r')==0 || (c^'\t')==0 || (c^'\v')==0 || (c^'\f')==0)) {
            c = ff.get();
        }
        // handles if the file is at end so it doesn't count the extra word
        if (!ff) break;
        // Once it encounters non character, parses entire word.
        while (ff && ((c^' ')!=0 && (c^'\n')!=0 && (c^'\r')!=0 && (c^'\t')!=0 && (c^'\v')!=0 && (c^'\f')!=0)) c = ff.get();
        words++;
    }

    ff.clear();
    ff.seekg(0, std::ios::beg);
    return words;
}

void FH::FF::close()
{
    ff.close();
}

void FH::FF::open(std::string file, ffmode mode)
{

    if (mode==FH::ffmode::BINARY){
        ff.open(file, std::ifstream::binary);
    } else {
        ff.open(file);
    }
    
    if (!ff.good()){
        std::cerr << "File \"" << file <<"\" does not exist\n";
        exit(1);
    }
}
