//
//  infix-postfix.cpp
//  
//
//  Created by Badri Tulsiram  and Michael Amezcua on 11/20/18.
//

#include<iostream>
#include<stack>
#include<string>

using namespace std;

string infix_postfix(string expression);

int precedence(char operator1, char operator2);

bool isOperator(char C);

bool isOperand(char C);

int main()
{
    string expression;
    cout<< "Enter a fully parenthesized infix expression: "<< endl;
    getline(cin, expression);
    string postfix = infix_postfix(expression);
    cout<< "Postfix expression is: " << postfix << endl;
}

string infix_postfix(string expression) {
    stack<char> shtack;
    string postfix = "";
    for (int i = 0;i< expression.length();i++) {
        if(expression[i] == ' ') continue;
        
        else if (isOperator(expression[i])) {
            while (!shtack.empty() && shtack.top() != '(' &&
                   precedence(shtack.top(),expression[i])) {
                postfix += shtack.top();
                shtack.pop();
            }
            shtack.push(expression[i]);
        }
        else if (isOperand(expression[i])) {
            postfix += expression[i];
        }
        
        else if (expression[i] == '(') {
            shtack.push(expression[i]);
        }
        
        else if (expression[i] == ')') {
            while (!shtack.empty() && shtack.top() != '(') {
                postfix += shtack.top();
                shtack.pop();
            }
            shtack.pop();
        }
        
    }
    
    while(!shtack.empty()) {
        postfix =+ shtack.top();
        shtack.pop();
    }
    
    return postfix;
}

bool isOperand(char C) {
    if (C >= '0' && C <= '9') return true;
    return false;
}

bool isOperator(char C)
{
    if(C == '+' || C == '-' || C == '*' || C == '/' || C== '^')
        return true;
    
    return false;
}

int isRightAssociative(char op)
{
    if(op == '^') return true;
    return false;
}


int getWeight(char op)
{
    int weight = -1;
    switch(op)
    {
        case '+':
        case '-':
            weight = 1;
        case '*':
        case '/':
            weight = 2;
        case '^':
            weight = 3;
    }
    return weight;
}

int precedence(char op1, char op2)
{
    int op1Weight = getWeight(op1);
    int op2Weight = getWeight(op2);
    
    // If operators have equal precedence, return true if they are left associative.
    // return false, if right associative.
    // if operator is left-associative, left one should be given priority.
    if(op1Weight == op2Weight)
    {
        if(isRightAssociative(op1)) return false;
        else return true;
    }
    return op1Weight > op2Weight ?  true: false;
}
