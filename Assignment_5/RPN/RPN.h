#pragma once
#include "../Stack/Stack.cpp"

using namespace std;

class RPN {
public:
    string infixToPostfix(string expression);
    bool isOperator(char token);
    bool isOperand(char token);
    int getPriority(char token);
    double rpn(string tokens);
};
