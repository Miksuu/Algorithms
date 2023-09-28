#include <iostream>
#include <random>
#include <chrono>
#include "ArrayTools.cpp"

// Finds the max element in an array
int findMaxElementInArray(int _arrayInput[], int _arrayLength) {
    int maxElement = 0;
    for (int i = 0; i < _arrayLength; ++i) {
        if (_arrayInput[i] > maxElement) {
            maxElement = _arrayInput[i];
        }
    }
    return maxElement;
}

// Function that takes some number amount (as parameter) and creates that amount of integers in array and finds the max element and prints it
void CreateSomeAmountOfRandomNumbersAndPlaceThemInArrayAndFindMaxElement(int _arrayLength, int _minNum, int _maxNum) {
    // Replaced with more random method because for loop was so fast that it generated the same result every time
    //std::srand(std::time(0));
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(_minNum, _maxNum);

    // Allocates the memory
    int* integerArray = new int[_arrayLength];

    for (int i = 0; i < _arrayLength; ++i) {
        integerArray[i] = distribution(generator);
    }
    std::cout << "\n";

    ArrayTools::printArray("Elements: ", integerArray, _arrayLength);

    int maxElement = findMaxElementInArray(integerArray, _arrayLength);
    std::cout << "Maximum Element: " << maxElement << "\n\n";

    // Remember to delete the array to free up the memory
    delete[] integerArray;
}

void ProgrammingTask11() {
    // Run 5 tests
    for (int i = 0; i < 5; ++i) {
        // Takes in as parameter: number amount, min number, max number (integers)
        CreateSomeAmountOfRandomNumbersAndPlaceThemInArrayAndFindMaxElement(20, -668, 1337);
    }
}

// Function to check if a number is prime
bool isPrime(int _n) {
    // 0 and 1 are not prime numbers
    if (_n <= 1) {
        return false; 
    }
    for (int i = 2; i <= _n / 2; i++) {
        if (_n % i == 0 && i < sqrt(_n)) {
            return false;
        }
    }

    return true;

}
void ProgrammingTask12() {
    //for (int n = 0; n < 99; ++n)
    //{
    //    std::cout << "Number: " << n << " is prime: " << isPrime(n) << "\n";
    //}

    isPrime(953);
}


//int main() {
//    //ProgrammingTask11();
//    ProgrammingTask12();
//
//    return 0;
//}