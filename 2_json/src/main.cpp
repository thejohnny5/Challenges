#include <iostream>
#include <string>
#include "json.hpp"

void usage(){
    std::cout << "Usage: json_parse <File>" << std::endl;
}

int main (int argc, char *argv[]) {
    
    // Check numbre of parameters
    if (argc < 2 || argc>3){
        usage();
        return 1;
    }
    
    // If run like 'wcww <file>'
    // print out "lines words chars"
    if (argc == 2){
        JSONParser* js = new JSONParser(argv[1]);
        js->parse();
        delete js;
        return 0;
    }
    

    return 0;
}
