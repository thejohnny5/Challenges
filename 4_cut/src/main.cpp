#include <iostream>
#include "Cut.hpp"
#include "../../parsing_util/src/Parser.hpp"
#include <sstream>

int main(int argc, char const *argv[])
{
    ArgumentParser parser = ArgumentParser("ccut");
    parser.addArgument("columns", 'f', "", true, "Columns to cut (0-indexed)", true);
    parser.addArgument("delimiter", 'd', "", false, "Delimiter to use (tab default)", true, "\t");
    bool good = parser.parse(argc, argv);
    if (!good){
        std::cerr << "Error parsing fields" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<int> cols = Cut::getPositions(parser.getArgumentValue("columns"));
    std::stringstream ss(parser.getDefault());
    Cut::print_split_string(ss, Cut::getChar(parser.getArgumentValue("delimiter")), cols);
    return 0;
}
