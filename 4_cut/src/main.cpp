#include <iostream>
#include "Cut.hpp"
#include "../../parsing_util/src/Parser.hpp"
#include <sstream>

void usage()
{
    std::cout << "Usage: ccut -f[ 1,2,3,etc] [-d] file" <<std::endl;
}

int main(int argc, char const *argv[])
{
    ArgumentParser parser;
    parser.addArgument("columns", 'f', "", true, true);
    parser.addArgument("delimiter", 'd', "", false, true, "\t");
    bool good = parser.parse(argc, argv);
    if (!good){
        std::cerr << "Error parsing fields" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<int> cols = getPositions(parser.getArgumentValue("columns"));
    for (auto &i: cols){
        std::cout << i << "\n";
    }
    std::stringstream ss(parser.getDefault());
    print_split_string(ss, '\t', cols);
    return 0;
}
