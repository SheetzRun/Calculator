//Anthony Phillips and Trevor Bender
//CSCI 330: Calculator
//Dr. Killian
//December 6th, 2020

#include <bits/c++config.h>
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

#include "List.hpp"

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
    enum token lex;
    double value;
};

struct lexeme tokens[10000];

enum type {
    Expr,
    Num
};

struct node {
    enum type type;
    union {
        struct {
            struct node* lhs;
            struct node* rhs;
            struct lexeme op;
        } expression;
        double val;
    };
};

struct node* root;
int i = 0, t = 0;

/********** FUNCTION DEFINITIONS **********/

void Calculator();

void lexicalAnalyzer();

void Parser();

int precedence(lexeme tok);

string association(token op);

bool op(int i);

struct node* term();

struct node* expr(int prev_precendence);

static struct node* makeTree(lexeme tok[]);

void Evaluator();

void printLexemes(lexeme lex);

/********** MAIN **********/

int main()
{
    Calculator();
}

/********** FUNCTION IMPLEMENTATIONS **********/

void Calculator()
{
    // Holds the lexemes and values of expression
    lexicalAnalyzer();
    Parser();
    // Evaluator();
}

void lexicalAnalyzer()
{
    char b[1024];
    // Get input expression from user
    cout << "Please enter an expression: ";
    scanf("%[a-z0-9+-*/()^. ]s", b);

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
    makeTree(tokens);
}

int precedence(lexeme tok){
    int precedence;
    switch (tok.lex) 
    {
    case PLUS:
    case MINUS:
        precedence = 0;
        break;
    case TIMES:
    case DIVIDES:
        precedence = 1;
        break;
    case POWER:
        precedence = 2;
        break;
    case LPAREN:
    case RPAREN:
    case NUMBER:
    case PI:
    case E:
        precedence = -1;
        break;
    }
    return precedence;
}

string association(token op) {
    string left_to_right;
    switch(op) {
        case PLUS:
        case MINUS:
        case TIMES:
        case DIVIDES:
        case NUMBER:
        case PI:
        case E:
            left_to_right = "left";
            break;
        case POWER:
            left_to_right = "right";
            break;
        default:
            break;
    }
    return left_to_right;
}

bool op(int i)
{
    switch(tokens[i].lex)
    {
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVIDES:
    case POWER:
        return true;
    case LPAREN:
    case RPAREN:
    case NUMBER:
    case PI:
    case E:
        return false;
    }
}

struct node* term() {
    struct node* n = new node;
    if(tokens[i++].lex == NUMBER) {
        n->val = tokens[i].value;
        n->type = Num;
        return n;
    }
    else if(tokens[i++].lex == PI) {
        n->val = 3.14159265358979;
        n->type = Num;
        return n;
    }
    else if(tokens[i++].lex == E) {
        n->val = 2.71828182845904;
        n->type = Num;
        return n;
    }
    else if(tokens[i++].lex == LPAREN) {
        n = expr(-1);
        if(tokens[i++].lex == RPAREN)
            return n;
    }
    else {
        // failure - expected number but got something else
    }

    return nullptr;
}

struct node* expr(int prev_precendence) {
    // struct node* lhs = root->expression.lhs;
    struct node* n = new node;
    struct node* lhs = term();
    struct node* rhs = nullptr;

    while(i < t) {
        // Check if it's an operator
        if(op(i))
        {
            int curr_precedence = precedence(tokens[i]);
            if(curr_precedence < prev_precendence) break;
            if(association(tokens[i].lex) == "left")
                rhs = expr(curr_precedence + 1);
            else
                rhs = expr(curr_precedence);

            n->expression.lhs = lhs;
            n->expression.rhs = rhs;
            n->expression.op = tokens[i];

            cout << n->expression.op.lex << endl;
       }
        i++;
    }


    cout << "++++++++++++++++++++++++++++++++++++" << endl;
    cout << &(n->expression.lhs->type) << ", ";
    cout << &(n->expression.rhs->type) << ", ";
    cout << &(n->expression.op) << endl;
    cout << "++++++++++++++++++++++++++++++++++++" << endl;

    return n;
}

static struct node* makeTree(lexeme tok[]) {
    if(tok) {
        // n->type = Expr;
        switch(tok[0].lex) {
            case DIVIDES:
            case PLUS:
            case TIMES:
            case POWER:
            case MINUS:
                // n->expression.lhs = makeTree(tok);
                // n->expression.rhs = makeTree(tok);
                // n->val = 0;
                break;
            default:
                // n->val = tokens[i].value;
                // n->expression.lhs = n->expression.rhs = NULL;
                break;
        }
        return expr(-1);
    }
    return NULL;
}

void Evaluator()
{

}

void printLexemes(lexeme lex) {
    switch(lex.lex) {
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
        cout << endl;
}
