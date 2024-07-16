#include <iostream>
#include "RPN/RPN.h"

using namespace std;

int main() {
    RPN rpn;
    string expression = "5 + 3 * 2";
    string postfix = rpn.infixToPostfix(expression);
    cout << postfix << endl;
    double solver = rpn.rpn(postfix);
    cout << solver;
}