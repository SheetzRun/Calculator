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

// struct node {

//     enum type type;
//     union {
//         struct {
//             struct node* lhs;
//             struct node* rhs;
//             struct lexeme op;
//         } expression;
//         double val;
//     };
// };

struct expression {
    struct node* lhs;
    struct node* rhs;
    struct lexeme op;
    // Default constructor
    expression()
    : lhs(nullptr)
    , rhs(nullptr)
    , op()
    {}

    expression(node* l, node* r, lexeme o)
    : lhs(l)
    , rhs(r)
    , op(o)
    {}
};

class node {
    public:
    enum type type;
    double val;
    struct expression expr;
    // Default constructor
    node()
    : type()
    , val(0)
    , expr()
    {}
    // Just a value (NumberNode)
    node(enum type t, double v)
    : type(t)
    , val(v)
    , expr()
    {}
    // ExpressionNode
    node(enum type t, double v, struct expression e)
    : type(t)
    , val(v)
    , expr(e)
    {}
};

struct node* root;
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

    root = expr(-1);
    for(auto it = tokens.begin(); it != tokens.end(); it++) {
        Evaluator(root);
        root = expr(-1);
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
    return false;
}

struct node* term(lexeme tok) {
    struct node* n;
    if(tok.lex == NUMBER) {
        n->val = tok.value;
        n->type = Num;
        return n;
    }
    else if(tok.lex == PI) {
        n->val = 3.14159265358979;
        n->type = Num;
        return n;
    }
    else if(tok.lex == E) {
        n->val = 2.71828182845904;
        n->type = Num;
        return n;
    }
    else if(tok.lex == LPAREN) {
        n = expr(-1);
        if(tok.lex == RPAREN)
            return n;
    }
    else {
        // failure - expected number but got something else
    }
    return nullptr;
}

struct node* expr(int prev_precendence) {
    struct node* n = new node();
    struct node* lhs = term(*tokens.begin());
    struct node* rhs = new node();

    while(tokens.size() > 0) {
        // auto oper = tokens.erase(tokens.begin());
        // tokens.pop_front();
        auto oper = tokens.erase(tokens.begin());
        // Check if it's an operator
        if(op(*oper))
        {
            int curr_precedence = precedence(*oper);
            if(curr_precedence < prev_precendence) { 
                // tokens.insert(oper, *oper);
                break;
            }
            cout << oper->lex << endl;
            if(association(oper->lex) == "left")
                rhs = expr(curr_precedence+1);
            else
                rhs = expr(curr_precedence);

            n->expr.lhs = lhs;
            cout << "lhs: " << lhs->val << endl;
            n->expr.rhs = rhs;
            cout << "rhs: " << rhs->val << endl;
            n->expr.op = oper->lex;
            cout << "op: " << oper->lex << endl;
        }
        oper++;
    }
    cout << endl;

    return n;
}

double Evaluator(struct node* node)
{

    cout << "EVALUATE THIS, BITCH" << endl;
    if(node->type == Expr) {
        cout << "eval this if" << endl;
        double lhs = Evaluator(node->expr.lhs);
        cout << "eval lhs: " << lhs << endl;
        double rhs = Evaluator(node->expr.rhs);
        cout << "eval rhs" << endl;

        // return lhs (node->expression.op.lex) rhs;
        cout << "switchblade" << endl;
        switch(node->expr.op.lex) {
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
        cout << "cut" << endl;
    }
    else {
        cout << "NUMBERNODE" << endl;
        return node->val; // It's a NumberNode
    }
}

// 1+2*3-8/(3-1) = 3

