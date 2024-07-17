#include "RPN.h"
#include <sstream>

bool RPN::isOperator(char token) {
    return token == '+' || token == '-' || token == '*' || token == '/';
}

bool RPN::isOperand(char token) {
    return isdigit(token) || token == '.';
}

bool RPN::isFunction(string token) {
    return token == "max" || token == "min" || token == "abs" || token == "pow";
}

bool RPN::isLetter(char token) {
    return isalpha(token);
}

int RPN::getPriority(char token) {
    switch (token) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return 0;
    }
}

string RPN::infixToPostfix(string expression) {
    string postfix;
    Stack<char> operators;
    string currentNumber;
    Stack<string> functions;
    string currentFunction;

    for (char element : expression) {
        if(isOperand(element)) {
            currentNumber += element;
        }
        else if(isLetter(element)) {
            currentFunction += element;
        }
        else {
            if(!currentNumber.empty()) {
                postfix += currentNumber + ' ';
                currentNumber = "";
            }
            if(!currentFunction.empty()) {
                functions.push(currentFunction);
                currentFunction = "";
            }
            if(element == '(') {
                operators.push(element);
            }
            else if(element == ',') {
                while (!operators.isEmpty() && operators.getTop() != '(') {
                    postfix += operators.getTop();
                    postfix += ' ';
                    operators.pop();
                }
            }
            else if(element == ')') {
                while (!operators.isEmpty() && operators.getTop() != '(') {
                    postfix += operators.getTop();
                    postfix += ' ';
                    operators.pop();
                }

                if (!operators.isEmpty()) {
                    operators.pop();
                }

                if (!functions.isEmpty()) {
                    postfix += functions.getTop();
                    postfix += ' ';
                    functions.pop();
                }
            }
            else if(isOperator(element)) {
                while(!operators.isEmpty() && getPriority(operators.getTop()) >= getPriority(element) && operators.getTop() != '(') {
                    postfix += operators.getTop();
                    postfix += ' ';
                    operators.pop();
                }
                operators.push(element);
            }
        }
    }

    if(!currentNumber.empty()) {
        postfix += currentNumber + ' ';
    }

    while(!operators.isEmpty()) {
        postfix += operators.getTop();
        postfix += ' ';
        operators.pop();
    }

    return postfix;
}

double RPN::rpn(string tokens) {
    Stack<double> rpntokens;
    string currentNumber;
    string currentFunction;
    istringstream tokenStream(tokens);
    string token;

    while(tokenStream >> token) {
        if(isFunction(token)) {
            double operand1 = rpntokens.getTop();
            rpntokens.pop();
            if(token == "abs") {
                rpntokens.push(abs(operand1));
            }
            else {
                double operand2 = rpntokens.getTop();
                rpntokens.pop();
                if(token == "max" ) {
                    rpntokens.push(max(operand2, operand1));
                }
                else if(token == "min" ) {
                    rpntokens.push(min(operand2, operand1));
                }
                else if(token == "pow" ) {
                    rpntokens.push(pow(operand2, operand1));
                }
            }
        }
        else if(isOperator(token[0]) && token.size() == 1) {
            char operation = token[0];
            double operand1 = rpntokens.getTop();
            rpntokens.pop();
            double operand2 = rpntokens.getTop();
            rpntokens.pop();

            switch (operation) {
                case '+': {
                    rpntokens.push(operand2 + operand1);
                    break;
                }
                case '-': {
                    rpntokens.push(operand2 - operand1);
                    break;
                }
                case '*': {
                    rpntokens.push(operand2 * operand1);
                    break;
                }
                case '/': {
                    if(operand1 == 0) {
                        cerr << "Division by zero!" << endl;
                        return 0;
                    }
                    rpntokens.push(operand2 / operand1);
                    break;
                }
            }
        } else {
            rpntokens.push(stod(token));
        }
    }
    return rpntokens.getTop();
}