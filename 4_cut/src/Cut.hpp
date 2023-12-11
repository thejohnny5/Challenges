#include <vector>
#include <memory>
#include <string>
#include <iostream>

namespace Cut{

// Overload to split string to work with string stream
std::vector<std::string> split_string(std::stringstream& s, const char& delim);

// Prints the string to stdout based on the positions and delimiter
void print_split_string(std::stringstream& string, const char& delim, std::vector<int>& positions);

// Splits string like "1,3,5,7" into a vector
std::vector<int> getPositions(std::string f);

// Returns first character of the string
char getChar(const std::string &s);
}