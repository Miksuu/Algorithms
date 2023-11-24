#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>

class MinHeap {
public:
    int *heapArray; 
    int capacity; 
    int heapSize; 

    int parent(int i) { return (i-1)/2; }

    int left(int i) { return (2*i + 1); }

    int right(int i) { return (2*i + 2); }

    MinHeap(int _cap) {
        heapSize = 0;
        capacity = _cap;
        heapArray = new int[_cap];
    }

    void insert(int _k) {
        if (heapSize == capacity) {
            std::cout << "\nOverflow: Could not insert the key\n";
            return;
        }

        heapSize++;
        int i = heapSize - 1;
        heapArray[i] = _k;

        while (i != 0 && heapArray[parent(i)] > heapArray[i]) {
        std::swap(heapArray[i], heapArray[parent(i)]);
        i = parent(i);
        }
    }

    int delMin() {
        if (heapSize <= 0)
            return INT_MAX;
        if (heapSize == 1) {
            heapSize--;
            return heapArray[0];
        }

        int root = heapArray[0];
        heapArray[0] = heapArray[heapSize-1];
        heapSize--;
        MinHeapify(0);

        return root;
    }

    void MinHeapify(int _i) {
        int l = left(_i);
        int r = right(_i);
        int smallest = _i;
        if (l < heapSize && heapArray[l] < heapArray[_i])
            smallest = l;
        if (r < heapSize && heapArray[r] < heapArray[smallest])
            smallest = r;
        if (smallest != _i) {
            std::swap(heapArray[_i], heapArray[smallest]);
            MinHeapify(smallest);
        }
    }

};

void ProgrammingTask81() {
    std::cout << "\n--------------PT81--------------\n";

    int size = 15;

    MinHeap minHeap(size);
    int arrayOfNumbers[] = {17, 11, 6, 14, 22, 8, 1, 16, 10, 19, 12, 3, 5, 15, 13};
    std::cout << "Before sorting: ";
    for(int i = 0; i < size; i++) {
        std::cout << arrayOfNumbers[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < size; i++) {
        minHeap.insert(arrayOfNumbers[i]);
    }
    int sortedArrayOfNumbers[size];
    for(int i = 0; i < size; i++) {
        sortedArrayOfNumbers[i] = minHeap.delMin();
    }
    std::cout << "After sorting: ";
    for(int i = 0; i < size; i++) {
        std::cout << sortedArrayOfNumbers[i] << " ";
    }
    std::cout << std::endl;

}

void ProgrammingTask82() {
    std::cout << "\n--------------PT82--------------\n";
    int sizes[] = {100000, 1000000, 10000000};
    srand(time(0));

    for(int s = 0; s < 3; s++) {
        int* array = new int[sizes[s]];
        for(int i = 0; i < sizes[s]; i++) {
            array[i] = rand() % sizes[s];
        }

        MinHeap minHeap(sizes[s]);

        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < sizes[s]; i++) {
            minHeap.insert(array[i]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

        delete[] array;
    }
}

int main() {
    ProgrammingTask81();
    ProgrammingTask82();

    // --------------PT82--------------
    // Time taken by function: 2276 microseconds
    // Time taken by function: 22901 microseconds
    // Time taken by function: 228920 microseconds

    return 0;
}