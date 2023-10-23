#include <iostream>
#include <chrono>
#include <random>
#include <utility>

void simpleSort(float _a[], int _n) {
    for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n; ++j) {
            if (_a[j] < _a[i]) {
                std::swap(_a[j], _a[i]);
            }
        }
    }
}

double measureTime(int _n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::chrono::duration<double> duration(0);

    float* floatArray = new float[_n];
    for (int i = 0; i < _n; ++i) {
        floatArray[i] = dis(gen);
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    simpleSort(floatArray, _n);
    auto endTime = std::chrono::high_resolution_clock::now();

    duration = endTime - startTime;

    delete[] floatArray;

    return duration.count();
}

void ProgrammingTask41() {
    int sizes[] = { 10000, 100000, 1000000 }; // Changed to lower times divided by 10 for shorter runtime
    int arraySizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < arraySizes; ++i) {
        double avgTime = measureTime(sizes[i]);
        std::cout << "Average time to sort " << sizes[i] << " elements: " << avgTime << " seconds" << std::endl;
    }
}

//int main() {
//    ProgrammingTask41();

    // Results:
    // I changed it to be from 10k to 1000k elements since the execution time was getting too high for 10000k elements and this proves the point either way
    // Average time to sort 10000 elements: 0.17627 seconds
    // Average time to sort 100000 elements : 15.3924 seconds
    // Average time to sort 1000000 elements : 1544.13 seconds
    // The Big O-notation is clearly visible here, the time does not scale linearly. It does follow the O(f(n)).
//
//    return 0;
//}