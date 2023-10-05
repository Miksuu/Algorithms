#include <iostream>
#include "ArrayTools.cpp"

void ProgrammingTask31(int _loopUntil) {
    int first = 0;
    int second = 1;
    int next = 0;

    for (int i = 2; true; ++i) {
        next = first + second;
        first = second;
        second = next;

        std::cout << second << "\n";

        if (second >= _loopUntil) {
            break;
        }
    }
}

void ProgrammingTask32() {

}

int main() {
    // Define the number of test cases for each of the linear and binary searches here
    ProgrammingTask31(13337);
    ProgrammingTask32();

    return 0;
}