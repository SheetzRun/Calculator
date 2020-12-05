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
#include <stdlib.h>

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

enum node_type {
    Expression,
    Number
};

struct Node {
    node_type type;
    union {
        struct {
            Node* lhs;
            Node* rhs;
            lexeme op;
        } expr;
        double num;
    };
};

/********** FUNCTION DEFINITIONS **********/

void Calculator();

vector<lexeme> lexicalAnalyzer();

void Parser(vector<lexeme> lex);

static Node* tree(Node* n);

Node* term(token tok);

Node* expr(int prev_precendence, vector<lexeme> lex);

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
    Parser(lexi);
    // Evaluator();
}

vector<lexeme> lexicalAnalyzer()
{
    // char expr[1024];
    lexeme tokens[1024];
    char b[1024];
    // Get input expression from user
    cout << "Please enter an expression: ";
    scanf("%[a-z0-9+-*/()^. ]s", b);

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
void Parser(vector<lexeme> lex)
{
    // expr(-1, lex);
}

static Node* tree(Node* n) {
    n = (Node*)malloc(sizeof(n));

    if(n==nullptr) return nullptr;

    n->type = Expression;
    switch(n->expr.op.lex) {
        case DIVIDES:
        case TIMES:
        case PLUS:
        case MINUS:
            n->expr.lhs = tree(n);
            n->expr.rhs = tree(n);
            n->num = 0;
            break;
        default:
            n->expr.lhs = n->expr.rhs = nullptr;
    }
    return n;
}

Node* term(lexeme tok) {
    if(tok.lex == NUMBER) {
        // return NumberNode(tok.value);
    }
    else if(tok.lex == PI) {
        // return NumberNode(3.14159...);
    }
    else if(tok.lex == E) {
        // return NumberNode(2.71828...);
    }
    else if(tok.lex == LPAREN) {
        // node <- expr()
        // assert(nextLexeme() is RPAREN)
        // return node;
    }
    else {
        // failure - expected number but got something else
    }

    return nullptr;
}

Node* expr(int prev_precendence, vector<lexeme> lex) {
    // lhs <- term()
    while(true) {
        // lexeme op <- nextLexeme() // Ensure that it's an operator
        int curr_precendence; // <- precendence(op);
        // if(op.lex==PLUS || op.lex==MINUS) curr_precendence = 0;
        // else if(op.lex==TIMES || op.lex==DIVIDES) curr_precendence = 1;
        // else if(op.lex==POWER) curr_precendence = 2;

        if(curr_precendence < prev_precendence) break;


        // lsh = ExpressionNode(lhs, op, rhs);
    }
    return nullptr;
}

void Evaluator()
{

}


