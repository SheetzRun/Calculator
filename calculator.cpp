//Anthony Phillips and Trevor Bender
//CSCI 330: Calculator
//Dr. Killian
//December 6th, 2020

#include <iomanip>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
#include <regex>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

/********** FUNCTION DEFINITIONS **********/

void Calculator();

void lexicalAnalyzer();

void Parser();

void Evaluator();


// Lexeme token enum
enum token {
    PLUS,
    MINUS,
    TIMES, 
    DIVIDES,
    POWER,
    LPAREN,
    RPAREN,
    NUMBER,
    PI,
    E
};
// Lexeme structure
struct lexeme {
    enum token lex;
    double value;
};

/********** MAIN **********/

int main()
{
    Calculator();
}

/********** FUNCTION IMPLEMENTATIONS **********/

void Calculator()
{
    // Get input expression from user
    // string expression;
    // cout << "Please enter an expression: ";
    // std::getline(cin, expression);
    lexicalAnalyzer();
    // Parser();
    // Evaluator();
}

void lexicalAnalyzer()
{
    char expr[1024];
    lexeme tokens[1024];
    // Read input into char array expr using format of regex
    // cout << "Please enter an expression: ";
    scanf("%[a-z0-9+-*/()^ ]s", expr);

    int count = 0;
    for(int i = 0; i < strlen(expr); i++) {
        if(std::isblank(expr[i])) {
            // Skip loop if is blank
            continue;
        }
        else if(expr[i]=='p') {
            if(expr[i+1]=='i') {
                tokens[count].lex = PI;
                ++count;
                ++i;
            }
        }
        else if(expr[i]=='e') {
            tokens[count].lex = E;
            ++count;
        }
        else if(std::isdigit(expr[i])) {
            char* end;
            char* begin = expr + i;
            double val;
            // Converts string to double
            val = strtod(begin, &end);
            i = (end - expr) - 1;
            tokens[count].lex = NUMBER;
            tokens[count].value = val;
            ++count;
        }
        else {
            switch(expr[i]) {
            case '+': 
                tokens[count].lex = PLUS;
                break;
            case '-': 
                tokens[count].lex = MINUS;
                break;
            case '*': 
                tokens[count].lex = TIMES;
                break;
            case '/': 
                tokens[count].lex = DIVIDES;
                break;
            case '^': 
                tokens[count].lex = POWER;
                break;
            case ')': 
                tokens[count].lex = RPAREN;
                break;
            case '(': 
                tokens[count].lex = LPAREN;
                break;
            }
            ++count;
        }
    }
    
    for(int i = 0; i < count; i++) {
        switch(tokens[i].lex) {
            case PLUS: 
                cout << "PLUS";
                break;
            case MINUS: 
                cout << "MINUS";
                break;
            case TIMES: 
                cout << "TIMES";
                break;
            case DIVIDES: 
                cout << "DIVIDES";
                break;
            case POWER: 
                cout << "POWER";
                break;
            case RPAREN: 
                cout << "RPAREN";
                break;
            case LPAREN: 
                cout << "LPAREN";
                break;
            case NUMBER: 
                cout << tokens[i].value;
                break;
            case PI: 
                cout << "PI";
                break;
            case E: 
                cout << "E";
                break;
            default:
                cout << "ERROR";
                break;
        }

        cout << " ";
    }
    cout << endl;
}

void Parser()
{

}

void Evaluator()
{

}


