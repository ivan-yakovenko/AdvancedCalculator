#include "RPN.h"

bool RPN::isOperator(char token) {
    return token == '+' || token == '-' || token == '*' || token == '/';
}

bool RPN::isOperand(char token) {
    return !isOperator(token) && token != '('&& token != ')' && token != ' ';
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

    for (char element : expression) {
        if(isOperand(element)) {
            currentNumber += element;
        }
        else {
            if(!currentNumber.empty()) {
                postfix += currentNumber + ' ';
                currentNumber = "";
            }
            if(element == '(') {
                operators.push(element);
            }
            else if(element == ')') {
                while(!operators.isEmpty() && operators.getTop() != '(') {
                    postfix += operators.getTop();
                    postfix += ' ';
                    operators.pop();
                }
                if (!operators.isEmpty()) {
                    operators.pop();
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

    for(char token : tokens) {
        if(isOperand(token)) {
            currentNumber += token;
        }
        else if(isspace(token)) {
            if(!currentNumber.empty()) {
                rpntokens.push(stod(currentNumber));
                currentNumber = "";
            }
        }
        else if(isOperator(token)) {
            if(!currentNumber.empty()) {
                rpntokens.push(stod(currentNumber));
                currentNumber = "";
            }
            double operand1 = rpntokens.getTop();
            rpntokens.pop();
            double operand2 = rpntokens.getTop();
            rpntokens.pop();

            switch (token) {
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
        }
    }
    return rpntokens.getTop();
}