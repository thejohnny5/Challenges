#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "Cut.hpp"
// // Splits a string based on the delim character
// std::vector<std::string> split_string(const std::string& s, const char& delim);

// Overload to split string to work with string stream
std::vector<std::string> Cut::split_string(std::stringstream& s, const char& delim) {
    std::vector<std::string> string_vec;
    std::string curr;

    while (s.good()) {
        char c = s.get();
        
        if (s.eof() || c == '\n' || c == delim) {
            if (!curr.empty()) {
                string_vec.push_back(curr);
                curr.clear();
            }

            if (s.eof() || c == '\n') {
                break;
            }
        } else {
            curr += c;
        }
    }

    return string_vec;
}

// Prints the string to stdout based on the positions and delimiter
void Cut::print_split_string(std::stringstream& string, const char& delim, std::vector<int>& positions)
{
    // Read in string continuously
        // call split string to get back vector
        // loop through positions, printing out string at each (if it exists) otherwise printout ""
    while (!string.eof()){
        std::vector<std::string> string_vec = split_string(string, delim);
     
        for (auto &num: positions){
            if (num<string_vec.size()) std::cout << string_vec[num] << " ";
            else std::cout << "  "; 
        }
        std::cout << std::endl;
    }
}


std::vector<int> Cut::getPositions(std::string f){
    std::vector<int> positions;
    std::stringstream ss(f);
    std::string token;

    while (std::getline(ss, token, ',')) {
        try {
            int pos = std::stoi(token);
            positions.push_back(pos);
        } catch (const std::invalid_argument& e) {
            // Handle or report the error if the token is not a valid integer
            std::cerr << "Invalid number: " << token << std::endl;
        } catch (const std::out_of_range& e) {
            // Handle or report the error if the number is too large for an int
            std::cerr << "Number out of range: " << token << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return positions;

}

char Cut::getChar(const std::string& s){
    return s[0];
    // if (s[0]=='\\'){
    //     // switch cases
    //     switch (s[1]){
    //         case 't':{
    //             return '\t';
    //         }
    //         case 'n':{
    //             return '\n';
    //         }
    //         case 'r':{
    //             return '\r';
    //         }
    //         default:{
    //             return '\0';
    //         }
    //     }
    // } else {
    //     return s[0];
    // }
}