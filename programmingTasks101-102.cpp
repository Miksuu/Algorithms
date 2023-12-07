#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <vector>
#include <random>

void shellSort(int _array[], int _size) {
    for (int _gap = _size/2; _gap > 0; _gap /= 2) {
        for (int _i = _gap; _i < _size; _i += 1) {
            int _temp = _array[_i];
            int _j;
            for (_j = _i; _j >= _gap && _array[_j - _gap] > _temp; _j -= _gap)
                _array[_j] = _array[_j - _gap];
            _array[_j] = _temp;
        }
    }
}

void merge(int _array[], int _left, int _mid, int _right) {
    int _i, _j, _k;
    int _n1 = _mid - _left + 1;
    int _n2 =  _right - _mid;
    std::vector<int> _L(_n1), _R(_n2); // Use vectors to avoid segmentation fault
    for (_i = 0; _i < _n1; _i++)
        _L[_i] = _array[_left + _i];
    for (_j = 0; _j < _n2; _j++)
        _R[_j] = _array[_mid + 1+ _j];
    _i = 0;
    _j = 0;
    _k = _left;
    while (_i < _n1 && _j < _n2) {
        if (_L[_i] <= _R[_j]) {
            _array[_k] = _L[_i];
            _i++;
        }
        else {
            _array[_k] = _R[_j];
            _j++;
        }
        _k++;
    }
    while (_i < _n1) {
        _array[_k] = _L[_i];
        _i++;
        _k++;
    }
    while (_j < _n2) {
        _array[_k] = _R[_j];
        _j++;
        _k++;
    }
}

void mergeSort(int _array[], int _left, int _right) {
    if (_left < _right) {
        int _mid = _left+(_right-_left)/2;
        mergeSort(_array, _left, _mid);
        mergeSort(_array, _mid+1, _right);
        merge(_array, _left, _mid, _right);
    }
}

int partition(int _array[], int _low, int _high) {
    int _pivot = _array[_high];
    int _i = (_low - 1);
    for (int _j = _low; _j <= _high- 1; _j++) {
        if (_array[_j] <= _pivot) {
            _i++;
            std::swap(_array[_i], _array[_j]);
        }
    }
    std::swap(_array[_i + 1], _array[_high]);
    return (_i + 1);
}

void quickSort(int _array[], int _low, int _high) {
    if (_low < _high) {
        int _pi = partition(_array, _low, _high);
        quickSort(_array, _low, _pi - 1);
        quickSort(_array, _pi + 1, _high);
    }
}

void printArray(int _array[], int _size) {
    for (int _i = 0; _i < _size; _i++)
        std::cout << _array[_i] << " ";
    std::cout << std::endl;
}

void randomizeArray(int _array[], int _size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _size - 1);
    for (int _i = _size - 1; _i > 0; _i--) {
        int _j = dis(gen);
        std::swap(_array[_i], _array[_j]);
    }
}

void ProgrammingTask101() {
    std::cout << "\n--------------PT101--------------\n";
    int array[] = {5, 2, 8, 6, 1, 9, 3, 7, 4, 0};
    int size = sizeof(array) / sizeof(array[0]);

    std::cout << "Original array: ";
    printArray(array, size);

    shellSort(array, size);
    std::cout << "Array after Shell sort: ";
    printArray(array, size);

    randomizeArray(array, size);

    mergeSort(array, 0, size - 1);
    std::cout << "Array after Merge sort: ";
    printArray(array, size);

    randomizeArray(array, size);

    quickSort(array, 0, size - 1);
    std::cout << "Array after Quick sort: ";
    printArray(array, size);
}

void testSortPerformance(int* _array, int _size, const std::string& _sortName, void (*_sortFunc)(int*, int)) {
    auto start = std::chrono::high_resolution_clock::now();
    _sortFunc(_array, _size);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by " << _sortName << ": " << duration.count() << " nanoseconds" << std::endl;
}

void shellSortWrapper(int* _array, int _size) {
    shellSort(_array, _size - 1);
}

void mergeSortWrapper(int* _array, int _size) {
    mergeSort(_array, 0, _size - 1);
}

void quickSortWrapper(int* _array, int _size) {
    quickSort(_array, 0, _size - 1);
}

void ProgrammingTask102() {
    std::cout << "\n--------------PT102--------------\n";
    int sizes[] = {100, 1000, 10000};

    for(int s = 0; s < 3; s++) {
        std::cout << "Size: " << sizes[s] << std::endl;
        int* array = new int[sizes[s]];

        for(int i = 0; i < sizes[s]; i++) {
            array[i] = i;
        }

        std::cout << "Testing with array in order: "<< std::endl;
        //printArray(array, sizes[s]);
        testSortPerformance(array, sizes[s], "Shell sort", shellSortWrapper);
        //printArray(array, sizes[s]);
        testSortPerformance(array, sizes[s], "Merge sort", mergeSortWrapper);
        //printArray(array, sizes[s]);
        testSortPerformance(array, sizes[s], "Quick sort", quickSortWrapper);

        for(int i = 0; i < sizes[s]; i++) {
            array[i] = sizes[s] - i - 1;
        }
        std::cout << "Testing with array in reverse order: "<< std::endl;
        //printArray(array, sizes[s]);
        testSortPerformance(array, sizes[s], "Shell sort", shellSortWrapper);
        testSortPerformance(array, sizes[s], "Merge sort", mergeSortWrapper);
        testSortPerformance(array, sizes[s], "Quick sort", quickSortWrapper);

        randomizeArray(array, sizes[s]);
        //printArray(array, sizes[s]);
        std::cout << "Testing with array in random order: "<< std::endl;
        testSortPerformance(array, sizes[s], "Shell sort", shellSortWrapper);
        testSortPerformance(array, sizes[s], "Merge sort", mergeSortWrapper);
        testSortPerformance(array, sizes[s], "Quick sort", quickSortWrapper);

        delete[] array;
    }
}

int main() {
    ProgrammingTask101();
    ProgrammingTask102();

    // --------------PT101--------------
    // Original array: 5 2 8 6 1 9 3 7 4 0
    // Array after Shell sort: 0 1 2 3 4 5 6 7 8 9
    // Array after Merge sort: 0 1 2 3 4 5 6 7 8 9
    // Array after Quick sort: 0 1 2 3 4 5 6 7 8 9

    // --------------PT102--------------
    // Size: 100
    // Testing with array in order:
    // Time taken by Shell sort: 1400 nanoseconds
    // Time taken by Merge sort: 310100 nanoseconds
    // Time taken by Quick sort: 20600 nanoseconds
    // Testing with array in reverse order:
    // Time taken by Shell sort: 2400 nanoseconds
    // Time taken by Merge sort: 244300 nanoseconds
    // Time taken by Quick sort: 20500 nanoseconds
    // Testing with array in random order:
    // Time taken by Shell sort: 4700 nanoseconds
    // Time taken by Merge sort: 304300 nanoseconds
    // Time taken by Quick sort: 25300 nanoseconds
    // Size: 1000
    // Testing with array in order:
    // Time taken by Shell sort: 17800 nanoseconds
    // Time taken by Merge sort: 929800 nanoseconds
    // Time taken by Quick sort: 2140600 nanoseconds
    // Testing with array in reverse order:
    // Time taken by Shell sort: 21400 nanoseconds
    // Time taken by Merge sort: 891300 nanoseconds
    // Time taken by Quick sort: 2281900 nanoseconds
    // Testing with array in random order:
    // Time taken by Shell sort: 75700 nanoseconds
    // Time taken by Merge sort: 1014000 nanoseconds
    // Time taken by Quick sort: 1938100 nanoseconds
    // Size: 10000
    // Testing with array in order:
    // Time taken by Shell sort: 275700 nanoseconds
    // Time taken by Merge sort: 31029900 nanoseconds
    // Time taken by Quick sort: 193130900 nanoseconds
    // Testing with array in reverse order:
    // Time taken by Shell sort: 375100 nanoseconds
    // Time taken by Merge sort: 32308100 nanoseconds
    // Time taken by Quick sort: 196227700 nanoseconds
    // Testing with array in random order:
    // Time taken by Shell sort: 999200 nanoseconds
    // Time taken by Merge sort: 31185400 nanoseconds
    // Time taken by Quick sort: 191678400 nanoseconds
    // PS C:\Projects\Algorithms>

    return 0;
}