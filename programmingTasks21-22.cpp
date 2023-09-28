#include <iostream>
#include <random>
#include <chrono>
#include "ArrayTools.cpp"

bool linearSearch(int _numberToSearchFor, const int* _arrayToSearchFrom, int _arraySize) {
    for (int i = 0; i < _arraySize; ++i) {
        if (_arrayToSearchFrom[i] == _numberToSearchFor) {
            return true;
        }
    }
    return false;
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

    // Running the test cases with linear search
    for (int tc = 0; tc < _testCasesCount; ++tc) {
        int numberToSearchFor = distribution(generator);
        bool found = linearSearch(numberToSearchFor, arrayToSearchFrom, arrayLength);

        std::cout <<"TC: " << tc << " | numberToSearchFor " << numberToSearchFor << " found: " << std::boolalpha << found << std::endl;
    }
    std::cout << "\n";
}

int main() {
    // Define the number of test cases here
    ProgrammingTask21(10);
    //ProgrammingTask22();

    return 0;
}