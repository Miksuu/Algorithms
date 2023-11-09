#include <iostream>
#include <stack>
#include <fstream>

class Stack {
private:
    std::stack<char> stack;
public:
    void push(char c) {
        stack.push(c);
    }
    void pop() {
        if (!stack.empty()) {
            stack.pop();
        }
    }
    char top() {
        if (!stack.empty()) {
            return stack.top();
        }
        return '\0';
    }
    bool isEmpty() {
        return stack.empty();
    }
};

bool isMatchingPair(char _character1, char _character2) {
    switch (_character1) {
        case '(':
            if (_character2 == ')') {
                return true;
            }
            break;
        case '{':
            if (_character2 == '}') {
                return true;
            }
            break;
        case '[':
            if (_character2 == ']') {
                return true;
            }
            break;
    }
    return false;
}

bool isSyntaxCorrect(std::string _input) {
    Stack stack;
    for (int i = 0; i < _input.length(); i++) {
        if (_input[i] == '{' || _input[i] == '(' || _input[i] == '[') {
            stack.push(_input[i]);
        }
        if (_input[i] == '}' || _input[i] == ')' || _input[i] == ']') {
            if (stack.isEmpty() || !isMatchingPair(stack.top(), _input[i])) {
                return false;
            } else {
                stack.pop();
            }
        }
    }
    return stack.isEmpty() ? true : false;
}

void ProgrammingTask61() {
    std::cout << "\n--------------PT61--------------\n";
    std::string input;
    std::cout << "Enter an expression:  "; 
    std::getline(std::cin, input);
    if (!isSyntaxCorrect(input)) {
        std::cout << "Incorrect syntax.\n";
        return;
    }
    std::cout << "Correct syntax.\n";    
}

std::string readFile(std::string _filename) {
    std::string input;
    std::string line;
    std::ifstream file(_filename);
    if (file.is_open()) {
        while (getline(file, line)) {
            input += line;
        }
        file.close();
    }
    return input;
}

void ProgrammingTask62() {
    std::cout << "\n--------------PT62--------------\n";
    std::string fileNames[] = {"correctSyntax.txt", "incorrectSyntax.txt"};
    std::string fileContent;

    for (int i = 0; i < 2; i++) {
        fileContent = readFile(fileNames[i]);
        std::cout << "Reading " << fileNames[i] << " with content: " << fileContent << ":\n";
        if (isSyntaxCorrect(fileContent)) {
            std::cout << "Correct syntax.\n";
        } else {
            std::cout << "Incorrect syntax.\n";
        }
    }
}

int main() {
    ProgrammingTask61();
    ProgrammingTask62();
    return 0;
}