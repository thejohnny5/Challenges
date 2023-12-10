#include <vector>
#include <memory>
#include <string>
#include <iostream>

// Splits a string based on the delim character
std::vector<std::string> split_string(const std::string& s, const char& delim);

// Overload to split string to work with string stream
std::vector<std::string> split_string(std::stringstream& s, const char& delim);

// Prints the string to stdout based on the positions and delimiter
void print_split_string(std::stringstream& string, const char& delim, std::vector<int>& positions);

std::vector<int> getPositions(std::string f);