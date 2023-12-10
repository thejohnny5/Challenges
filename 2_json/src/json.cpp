#include "json.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

Tokenizer::Tokenizer(std::string fileName)
{
    file.open(fileName);
    if (!file.good()) exit(1);
}

char Tokenizer::getWithoutWhiteSpace(){
    char c = ' ';
    while (file.good() && (c==' ' || c=='\n'))
    {
        c = file.get();
        if (!file.good() && (c==' ' || c=='\n')){
            std::cout << "error" << std::endl;
            exit(1);
        }
        // Error with file (or closed file)
        if (!file.good()) return c;
    }

    return c;
}

void Tokenizer::rollBackToken(){
    file.clear();
    file.seekg(prevPos);
}

void JSONParser::parse(){
    Token t;
    while (tokenizer.hasMoreTokens()) {
        t = tokenizer.getToken();
        std::cout << t.toString() << std::endl;
        switch (t.type) {
            case TOKEN::CURLY_OPEN:{
                std::unique_ptr<JSONNode> objectToken = parseObject();
                break;
            } 
            default:{
                std::cout << "Not valide" << std::endl;
                exit(1);
            }
        }
    
    }
}

std::unique_ptr<JSONNode> parseObject()
{
    Token t;
    t = tokenizer.getToken();
    std::cout<<t.toString() << "Done parseObj" << std::endl;
    return std::make_unique<JSONNode>(t);
}

