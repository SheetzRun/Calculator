//Anthony Phillips and Trevor Bender
//CSCI 330: Calculator
//Dr. Killian
//December 6th, 2020

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

// Lexeme token enum
enum token {
    PLUS,       // 0
    MINUS,      // 1
    TIMES,      // 2
    DIVIDES,    // 3
    POWER,      // 4
    LPAREN,     // 5
    RPAREN,     // 6
    NUMBER,     // 7
    PI,         // 8
    E           // 9
};
// Lexeme Structure
struct lexeme {
    token lex;
    double value;
};

// struct NumberNode {
//     double value;
// };

// struct ExpressionNode {
//     // LHS
//     // RHS
//     token lex;
// };

struct Node {
    using NodePtr = Node*;

    NodePtr LHS;
    NodePtr RHS;
    token lex;
};

struct NumberNode {
    double value;
};

struct ExpressionNode {
    Node l;
    Node r;
    token lex;
};

/********** FUNCTION DEFINITIONS **********/

void Calculator();

vector<lexeme> lexicalAnalyzer();

void Parser();

void Evaluator();

/********** MAIN **********/

int main()
{
    Calculator();
}

/********** FUNCTION IMPLEMENTATIONS **********/

void Calculator()
{
    // Holds the lexemes and values of expression
    vector<lexeme> lexi = lexicalAnalyzer();
    Parser();
    // Evaluator();
}

vector<lexeme> lexicalAnalyzer()
{
    // char expr[1024];
    lexeme tokens[1024];
    char b[1024];
    // Get input expression from user
    cout << "Please enter an expression: ";
    scanf("%[a-z0-9+-*/()^ ]s", b);

    int t = 0;
    for(int i = 0; i < strlen(b); i++) {
        if(std::isblank(b[i])) {
            // Skip loop if is blank
            continue;
        }
        else if(b[i]=='p') {
            // cout << "b[i+1]: " << b[i+1] << endl;
            if(b[i+1]=='i') {
                tokens[t].lex = PI;
                tokens[t].value = 3.14159265358979;
                ++t;
                ++i;
            }
        }
        else if(b[i]=='e') {
            tokens[t].lex = E;
            tokens[t].value = 2.71828182845904;
            ++t;
        }
        else if(std::isdigit(b[i])) {
            char* end;
            char* begin = b + i;
            double val;
            // Converts string to double
            val = strtod(begin, &end);
            i = (end - b) - 1;
            tokens[t].lex = NUMBER;
            tokens[t].value = val;
            ++t;
        }
        else {
            switch(b[i]) {
            case '+': 
                tokens[t].lex = PLUS;
                break;
            case '-': 
                tokens[t].lex = MINUS;
                break;
            case '*': 
                tokens[t].lex = TIMES;
                break;
            case '/': 
                tokens[t].lex = DIVIDES;
                break;
            case '^': 
                tokens[t].lex = POWER;
                break;
            case ')': 
                tokens[t].lex = RPAREN;
                break;
            case '(': 
                tokens[t].lex = LPAREN;
                break;
            }
            ++t;
        }
    }
    
    for(int i = 0; i < t; i++) {
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

    // Add values to vector to be returned
    vector<lexeme> lex;
    for(int i = 0; i < t; i++) {
        lex.push_back(tokens[i]);
    }

    return lex;
}

/*
 * Addition       : + : Left  : 0
 * Subtraction    : - : Left  : 0
 * Multiplication : * : Left  : 1
 * Division       : / : Left  : 1
 * Exponentiation : ^ : Right : 2
 */
void Parser()
{
    
}

void Evaluator()
{

}


