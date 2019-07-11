//
//  postfix.cpp
//  
//
//  Created by Badri Tulsiram on 11/19/18.
//

#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

using namespace std;

enum TokenType {ADD, SUBTRACT, MULTIPLY, DIVIDE, NUMBER, OTHER};

TokenType identify(char *t);

TokenType identify(char *t) {
    if (strcmp(t, "+") == 0)
        return ADD;
    if (strcmp(t, "-") == 0)
        return SUBTRACT;
    if (strcmp(t, "*") == 0)
        return MULTIPLY;
    if (strcmp(t, "/") == 0)
        return DIVIDE;
    double value;
    if (sscanf(t, "%g", &value) == 1)
        return NUMBER;
    return OTHER;
}

#define MAXLEN 100

double postfix_eval(char *expression[], int numTokens) {
    stack<double> numbers;
    double result = 0;
    TokenType type;
    
    for (int i=0; i<numTokens; i++) {
        type = identify(expression[i]);
        switch(type) {
            case NUMBER:
                numbers.push( atof(expression[i]));
                break;
                
            case ADD:
                if (numbers.empty())
                    throw string("empty stack where two numbers expected");
                result = numbers.top();
                numbers.pop();
                result = result + numbers.top();
                numbers.pop();
                numbers.push(result);
                break;
                
            case SUBTRACT:
                if (numbers.empty())
                    throw string("empty stack where two numbers expected");
                result = numbers.top();
                numbers.pop();
                result = numbers.top() - result;
                numbers.pop();
                numbers.push(result);
                break;/Users/badritulsiram/Downloads/Amihay, Time and Space.pdf
                
            case MULTIPLY:
                if (numbers.empty())
                    throw string("empty stack where two numbers expected");
                result = numbers.top();
                numbers.pop();
                result = result * numbers.top();
                numbers.pop();
                numbers.push(result);
                break;
                
            case DIVIDE:
                if (numbers.empty())
                    throw string("empty stack where two numbers expected");
                result = numbers.top();
                numbers.pop();
                result = numbers.top() / result;
                numbers.pop();
                numbers.push(result);
                break;
                
            default:
                throw string ("unknown token: ")
                + string(expression[i]);
        }
    }
    
    if (numbers.empty())
        throw string("empty stack where one result should be");
    result = numbers.top();
    numbers.pop();
    if (!numbers.empty())
        throw string("number(s) left on stack at end");
    
    return result;
}

int main(){
    
    char input[MAXLEN], *tokens[MAXLEN/2];

    cout << "enter an expression: ";
    cin.getline(input, MAXLEN);
    
    char *ptr = strtok(input, " ");
    
    int count = 0;
    while (ptr != 0) {
        tokens[count] = ptr;
        ++count;
        ptr = strtok(0, " ");
    }
    
    try {
        double result = postfix_eval(tokens, count);
        cout << "result: " << result << endl;
    }
    catch(string error) {
        cerr << "bad expression: " << error << endl;
        return 1;
    }
    
    return 0;
}
