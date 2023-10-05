#include <iostream>
#include "ArrayTools.cpp"

void ProgrammingTask31() {
    int first = 0;
    int second = 1;
    int next = 0;

    for (int i = 2; i <= 1000; ++i) {
        next = first + second;
        first = second;
        second = next;
        std::cout << second << "\n";
    }
}

void ProgrammingTask32() {

}

int main() {
    // Define the number of test cases for each of the linear and binary searches here
    ProgrammingTask31();
    ProgrammingTask32();

    return 0;
}