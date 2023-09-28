#include <iostream>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <iterator>
#include "ArrayTools.cpp"
#include "MemoryTools.cpp"

void DoPointerArrayStuff() {
    const long long* arrayLengthPointer = new long long(1000000);
    const int* maxNumberValue = new int(127917291);

    std::string memoryUsageTest = MemoryTools::getVirtualMemoryUsageWindowsInMB();
    std::cout << "Before allocating first array " + memoryUsageTest + "\n";

    // Array of integers using dynamic memory allocation
    long long* pointerLongLongArray = new long long[*arrayLengthPointer];

    memoryUsageTest = MemoryTools::getVirtualMemoryUsageWindowsInMB();
    std::cout << "After allocating first array " + memoryUsageTest + "\n";

    long long* pointerLongLongArrayCopy = new long long[*arrayLengthPointer];

    memoryUsageTest = MemoryTools::getVirtualMemoryUsageWindowsInMB();
    std::cout << "After allocating second array " + memoryUsageTest + "\n";

    // Store random integer values in to the array
    for (int i = 0; i < *arrayLengthPointer; i++)
    {
        std::string memoryUsage = MemoryTools::getVirtualMemoryUsageWindowsInMB();

        pointerLongLongArray[i] = std::rand() % *maxNumberValue + 1;

        //std::cout << "element: " << pointerLongLongArray[i] << " added to the list | memoryUsage: " << memoryUsage << std::endl; 
    }

    // Copy the array elements
    for (int i = 0; i < *arrayLengthPointer; i++)
    {
        pointerLongLongArrayCopy[i] = pointerLongLongArray[i];
    }

    ArrayTools::printArray("printing array copy: ", pointerLongLongArrayCopy, 5);

    // Release the memory
    delete[] pointerLongLongArray;
    
    // Causes access violation
    //ArrayTools::printArray("printing array copy: ", pointerLongLongArray, 5);

    std::string memoryUsageAfterReleasingMemory = MemoryTools::getVirtualMemoryUsageWindowsInMB();
    std::cout << "After deleting: " + memoryUsageAfterReleasingMemory + "\n";

    delete[] pointerLongLongArrayCopy;

    memoryUsageAfterReleasingMemory = MemoryTools::getVirtualMemoryUsageWindowsInMB();
    std::cout << "After deleting 2nd array: " + memoryUsageAfterReleasingMemory + "\n";
}

// Old method for the first lesson
void DoNonPointerArrayStuff() {
    std::srand(std::time(0));  // seed the random number generator

    int integerArray[10];  // array to hold 10 integers
    int integerArrayLength = std::size(integerArray);  // get the length of the array
    int maxNumberValue = 1000;

    // Populate the array with random numbers between 1 and maxNumberValue
    for (int i = 0; i < integerArrayLength; ++i) {
        integerArray[i] = std::rand() % maxNumberValue + 1;
    }

    // Display the random array elements
    std::cout << "Array elements: ";
    for (int i = 0; i < integerArrayLength; ++i) {
        std::cout << integerArray[i] << " ";
    }

    std::cout << std::endl;

    // Find the maximum element in the array
    int min_val = *std::min_element(integerArray, integerArray + integerArrayLength);
    std::cout << "Minimum element: " << min_val << std::endl;

    // Calculate the average of array elements using a one-liner
    float average = std::accumulate(integerArray, integerArray + integerArrayLength, 0) / static_cast<float>(integerArrayLength);
    std::cout << "Average of elements (calculated using one-liner): " << average << std::endl;

    // Find the maximum element in the array
    int max_val = *std::max_element(integerArray, integerArray + integerArrayLength);
    std::cout << "Maximum element: " << max_val << std::endl;
}

//int main() {
//    DoPointerArrayStuff();
//
//    return 0;
//}