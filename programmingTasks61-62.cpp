#include <iostream>
#include <stack>

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

int main() {
    ProgrammingTask61();
    return 0;
}