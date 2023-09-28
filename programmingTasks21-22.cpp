#include <iostream>
#include <random>
#include <chrono>
#include "ArrayTools.cpp"

bool linearSearch(int _numberToSearchFor, const int* _arrayToSearchFrom, int _arrayLength) {
    for (int i = 0; i < _arrayLength; ++i) {
        if (_arrayToSearchFrom[i] == _numberToSearchFor) {
            return true;
        }
    }
    return false;
}

bool binarySearch(int _numberToSearchFor, const int* _arrayToSearchFrom, int _arrayLength) {
    int left = 0, right = _arrayLength - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (_arrayToSearchFrom[mid] == _numberToSearchFor) {
            return true;
        }
        if (_arrayToSearchFrom[mid] < _numberToSearchFor) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return false;
}

// Running the test cases with linear search
void performLinearSearchOperations(int _testCasesCount, std::uniform_int_distribution<int> _distribution, std::mt19937 _generator,
    const int* _arrayToSearchFrom, int _arrayLength) {
    for (int tc = 0; tc < _testCasesCount; ++tc) {
        int numberToSearchFor = _distribution(_generator);
        bool found = linearSearch(numberToSearchFor, _arrayToSearchFrom, _arrayLength);

        std::cout << "performLinearSearchOperations(): TC " << tc << " | numberToSearchFor " << numberToSearchFor << " found: "
            << std::boolalpha << found << std::endl;
    }
    std::cout << "\n";
}

// Running the test cases with binary search
void performBinarySearchOperations(int _testCasesCount, std::uniform_int_distribution<int> _distribution, std::mt19937 _generator,
    const int* _arrayToSearchFrom, int _arrayLength) {
    for (int tc = 0; tc < _testCasesCount; ++tc) {
        int numberToSearchFor = _distribution(_generator);
        bool found = binarySearch(numberToSearchFor, _arrayToSearchFrom, _arrayLength);

        std::cout << "performBinarySearchOperations(): TC " << tc << " | numberToSearchFor " << numberToSearchFor << " found: "
            << std::boolalpha << found << std::endl;
    }
    std::cout << "\n";
}

void ProgrammingTask21(int _testCasesCount) {
    int arrayToSearchFrom[] = {1, 4, 6, 11, 13, 16, 19, 20, 25, 27, 29, 30, 32, 36, 39, 42, 45, 48, 49, 53};
    int arrayLength = sizeof(arrayToSearchFrom) / sizeof(arrayToSearchFrom[0]);
    ArrayTools::printArray("Array: ", arrayToSearchFrom, arrayLength);

    // Re-using some code from previous assignment, find max element to define the max number to search for during the test cases (min from 0)
    int maxElementToSearchFor = ArrayTools::findMaxElementInArray(arrayToSearchFrom, arrayLength);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, maxElementToSearchFor);

    performLinearSearchOperations(_testCasesCount, distribution, generator, arrayToSearchFrom, arrayLength);
    performBinarySearchOperations(_testCasesCount, distribution, generator, arrayToSearchFrom, arrayLength);
}

void ProgrammingTask22(int _testCasesCount) {
    for (int tc = 0; tc < _testCasesCount; ++tc) {
        std::cout << "ProgrammingTask22() : TC " << tc << "\n";

        int timesToRun[] = { 1000, 100000, 10000000 };
        for (int length : timesToRun) {
            int* arrayToSearchFrom = new int[length];
            for (int i = 0; i < length; ++i) {
                arrayToSearchFrom[i] = i + 1;
            }

            int maxElementToSearchFor = ArrayTools::findMaxElementInArray(arrayToSearchFrom, length);
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::mt19937 generator(seed);
            std::uniform_int_distribution<int> distribution(0, maxElementToSearchFor);

            int randomValue = distribution(generator);

            // Measuring Linear Search
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 10; ++i) {
                linearSearch(randomValue, arrayToSearchFrom, length);
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Linear Search Time for length " << length << ": " << duration.count() / 10.0 << " microseconds" << std::endl;

            // Measuring Binary Search
            start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 10; ++i) {
                binarySearch(randomValue, arrayToSearchFrom, length);
            }
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Binary Search Time for length " << length << ": " << duration.count() / 10.0 << " microseconds" << std::endl;

            delete[] arrayToSearchFrom;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    // Define the number of test cases for each of the linear and binary searches here
    ProgrammingTask21(10);
    ProgrammingTask22(10);

    return 0;
}