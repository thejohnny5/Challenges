#include <memory>
#include <iostream>

namespace sort{

// void Sort(std::istream& s, bool (*func)(void* s1, void* s2));

void quickSort(std::vector<int>& arr, int low, int high);

void merge_sort(std::vector<int>& arr);

// void heap_sort(std::vector<int>& vec);

// void radix_sort(std::vector<int>& vec);

}
