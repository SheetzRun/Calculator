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
#include <list>
#include <iterator>

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

    lexeme() 
    : lex()
    , value(0)
    {}

    lexeme(token tok)
    : lex(tok)
    , value(0)
    {}

    lexeme(token tok, double val) 
    : lex(tok)
    , value(val)
    {}
};

// struct lexeme tokens[10000];
std::list<lexeme> tokens;

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

// struct node* root;
int t=0;
auto i = tokens.begin();

/********** FUNCTION DEFINITIONS **********/

void Calculator();

void lexicalAnalyzer();

void Parser();

int precedence(lexeme tok);

string association(token op);

bool op(int i);

struct node* term(lexeme tok);

struct node* expr(int prev_precendence);

double Evaluator(struct node* node);

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
    // Parser();
    // Evaluator();

    for(auto it = tokens.begin(); it != tokens.end(); it++) {
        Evaluator(expr(-1));
    }
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
            if(b[i+1]=='i') {
                tokens.push_back(lexeme(PI, 3.14159265358979));
                ++t;
                ++i;
            }
        }
        else if(b[i]=='e') {
            tokens.push_back(lexeme(E, 2.71828182845904));
            ++t;
        }
        else if(std::isdigit(b[i])) {
            char* end;
            char* begin = b + i;
            double val;
            // Converts string to double
            val = strtod(begin, &end);
            i = (end - b) - 1;
            tokens.push_back(lexeme(NUMBER, val));
            ++t;
        }
        else {
            switch(b[i]) {
            case '+': 
                tokens.push_back(lexeme(PLUS));
                break;
            case '-': 
                tokens.push_back(lexeme(MINUS));
                break;
            case '*': 
                tokens.push_back(lexeme(TIMES));
                break;
            case '/': 
                tokens.push_back(lexeme(DIVIDES));
                break;
            case '^': 
                tokens.push_back(lexeme(POWER));
                break;
            case ')': 
                tokens.push_back(lexeme(RPAREN));
                break;
            case '(': 
                tokens.push_back(lexeme(LPAREN));
                break;
            }
            ++t;
        }
    }
    
    for(auto k = tokens.begin(); k != tokens.end(); k++) {
        
        switch(k->lex) {
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
                cout << k->value;
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
    // makeTree(tokens);
    // Call expr to get node that is root of tree
    // expr and term together should build the tree
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

bool op(lexeme i)
{
    switch(i.lex)
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
    struct node* n;
    if(i->lex == NUMBER) {
        n->val = i->value;
        n->type = Num;
        return n;
    }
    else if(i->lex == PI) {
        n->val = 3.14159265358979;
        n->type = Num;
        return n;
    }
    else if(i->lex == E) {
        n->val = 2.71828182845904;
        n->type = Num;
        return n;
    }
    else if(i->lex == LPAREN) {
        n = expr(-1);
        if(i->lex == RPAREN)
            return n;
    }
    else {
        // failure - expected number but got something else
    }

    return nullptr;
}

struct node* expr(int prev_precendence) {
    struct node* n;
    struct node* lhs = term(*tokens.begin());
    struct node* rhs = nullptr;

    cout << "outside while" << endl;

    while(tokens.size() > 0) {
        cout << "inside while" << endl;

        auto oper = tokens.begin();
        tokens.pop_front();

        // Check if it's an operator
        if(op(*oper))
        {
            int curr_precedence = precedence(*oper);
            if(curr_precedence < prev_precendence) break;
            if(association(oper->lex) == "left")
                rhs = expr(curr_precedence + 1);
            else
                rhs = expr(curr_precedence);


            cout << "assign this shit" << endl;

            n->expression.lhs = lhs;
            cout << "lhs: " << lhs << endl;
            n->expression.rhs = rhs;
            cout << "rhs: " << rhs << endl;
            n->expression.op = oper->lex;
            cout << "op: " << oper->lex << endl;
       }
        oper++;
    }
    cout << endl;

    // cout << "++++++++++++++++++++++++++++++++++++" << endl;
    // cout << &(n->expression.lhs->type) << ", ";
    // cout << &(n->expression.rhs->type) << ", ";
    // cout << &(n->expression.op) << endl;
    // cout << "++++++++++++++++++++++++++++++++++++" << endl;

    return n;
}

double Evaluator(struct node* node)
{
    if(node->type == Expr) {
        double lhs = Evaluator(node->expression.lhs);
        double rhs = Evaluator(node->expression.rhs);

        // return lhs (node->expression.op.lex) rhs;
        switch(node->expression.op.lex) {
            case PLUS:
                return lhs + rhs;
            case MINUS:
                return lhs - rhs;
            case TIMES:
                return lhs * rhs;
            case DIVIDES:
                return lhs / rhs;
            case POWER:
                return pow(lhs, rhs);
            default:
                return 0;
        }
    }
    else {
        return node->val; // It's a NumberNode
    }
}

// 1+2*3-8/(3-1) = 3

