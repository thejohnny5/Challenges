#include <iostream>
#include "Sort.hpp"
#include <vector>
void print_vec(const std::vector<int>& vec){
    for (auto &c: vec){
        std::cout << c << " ";
    }
    std::cout << std::endl;
};

int main (int argc, char *argv[]) {
    std::vector<int> test { 1, 8, 7, 10, -5, 20, 40, 3, 2, -10 };
    print_vec(test);

    // sort::merge_sort(test);
    sort::quickSort(test, 0, test.size()-1);
    print_vec(test);
    std::vector<int> test2 { 1, 8, 7, 10, -5, 20, 40, 3, 2, -10, -1 };
    print_vec(test2);

    //sort::merge_sort(test2);
    sort::quickSort(test2, 0, test2.size()-1);
    print_vec(test2);
    return 0;
};
