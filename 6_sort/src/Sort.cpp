#include "Sort.hpp"

void sort::merge_sort(std::vector<int>& arr){
    if (arr.size()<=1) return;
    
    int mid = arr.size()/2;
    std::vector<int>left(arr.begin(), arr.begin()+mid);
    std::vector<int> right (arr.begin()+mid, arr.end());
    merge_sort(left);
    merge_sort(right);
    
    int l=0, r=0; 
    while (l<left.size() && r<right.size()){
        if (left[l]<right[r])
        {
            arr[l+r] = left[l];
            l++;
        } else {
            arr[l+r] = right[r];
            r++;
        }
    }
    while (l<left.size()){
        arr[l+r] = left[l];
        l++;
    }

    while (r<right.size()){
        arr[l+r] = right[r];
        r++;
    }
}


int partition(std::vector<int> &arr, int low, int high) {
    int pivot = arr[high]; // Taking the last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // Increment the index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// QuickSort function
void sort::quickSort(std::vector<int> &arr, int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(std::vector<int>& arr);

void heapSort(std::vector<int>& arr);
