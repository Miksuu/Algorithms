#include <iostream>
#include <vector>
#include "ArrayTools.cpp"
#include <string>

void ProgrammingTask31(int _loopUntil) {
    std::vector<int> fibonacciNumbers;

    int first = 0;
    int second = 1;
    int next = 0;

    fibonacciNumbers.push_back(first);
    fibonacciNumbers.push_back(second);

    for (int i = 2; true; ++i) {
        next = first + second;
        first = second;
        second = next;

        fibonacciNumbers.push_back(second);

        if (second >= _loopUntil) {
            break;
        }
    }

    int* fibonacciArray = &fibonacciNumbers[0];
    int arraySize = fibonacciNumbers.size();

    ArrayTools::printArray("Fibonacci Numbers: ", fibonacciArray, arraySize);
}

int ackermannFunctionRecursive(int _m, int _n) {
    if (_m == 0) {
        return _n + 1;
    }

    if (_m > 0 && _n == 0) {
        return ackermannFunctionRecursive(_m - 1, 1);
    }

    return ackermannFunctionRecursive(_m - 1, ackermannFunctionRecursive(_m, _n - 1));
}

void ProgrammingTask32(int _m, int _n, int _loopIterationsCount) {
    std::vector<std::string> results;

    for (int i = 0; i < _loopIterationsCount; ++i) {
        int result = ackermannFunctionRecursive(_m, _n);
        std::string resultStr = "Ackermann(" + std::to_string(_m) + ", " + 
            std::to_string(_n) + ") = " + std::to_string(result);
        results.push_back(resultStr);

        // Increasing N +1 on every loop.
        _n += 1;
    }

    // Print the results of the string vector
    for (const auto& str : results) {
        std::cout << str << std::endl;
    }
}
//
//int main() {
//    ProgrammingTask31(13337);
//
//    // With m=3, n=2, _loopIterationsCount > 7 causes stack overflow
//    ProgrammingTask32(3, 2, 7);
//
//    return 0;
//}