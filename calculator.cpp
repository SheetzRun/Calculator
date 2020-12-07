//Anthony Phillips and Trevor Bender
//CSCI 330: Calculator
//Dr. Killian
//December 6th, 2020

/********** SYSTEM INCLUDES **********/
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


/********** USING DECLARATIONS **********/
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
    // Default constructor
    lexeme() 
    : lex()
    , value(0)
    {}
    // Constructor for just a token
    lexeme(token tok)
    : lex(tok)
    , value(0)
    {}
    // Constructor for both value and token
    lexeme(token tok, double val) 
    : lex(tok)
    , value(val)
    {}
};
// List to hold lexemes
std::list<lexeme> tokens;
// Used for assigning type to a node
enum type {
    Expr,
    Num
};
// Expression class
class expression {
    public:
        struct node* lhs;
        struct node* rhs;
        struct lexeme op;
        // Default constructor
        expression()
        : lhs(nullptr)
        , rhs(nullptr)
        , op()
        {}
        // Holds node* for left and right, and the operator
        expression(node* l, node* r, lexeme o)
        : lhs(l)
        , rhs(r)
        , op(o)
        {}
};
// Node class
class node {
    public:
        enum type type;
        double val;
        expression expr;
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

struct node* root = new node();
int t=0;
// Iterator to traverse through tokens list
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

/* Calculator
 * Controller for program
 */
void Calculator()
{
    // Holds the lexemes and values of expression
    lexicalAnalyzer();
    root = expr(-1);
    for(auto it = tokens.begin(); it != tokens.end(); it++) {
        Evaluator(root); 
    }
}

/* lexicalAnalyzer
 * lexicalAnalyzer does not have any parameters.
 * Used to create a list of lexemes to be used 
 * in an expression parser.
 * Return - void
 */
void lexicalAnalyzer()
{
    // Used to store input from user.
    char b[1024];
    // Get input expression from user
    cout << "Please enter an expression: ";
    // Scan input into char array b
    // Accepts letters, digits, spaces,
    // +, -, *, /, (, ), ^, and .
    scanf("%[a-z0-9+-*/()^. ]s", b);

    for(int i = 0; i < strlen(b); i++) {
        // Skip if char is a space
        if(std::isblank(b[i])) {
            continue;
        }
        // Check if current and next char equal 'pi'
        else if(b[i]=='p') {
            if(b[i+1]=='i') {
                // Add constant PI to back of tokens list
                tokens.push_back(lexeme(PI, 3.14159265358979));
                ++t;
                ++i;
            }
        }
        // Check if current char is 'e'
        else if(b[i]=='e') {
            // Add constant E to back of tokens list
            tokens.push_back(lexeme(E, 2.71828182845904));
            ++t;
        }
        // Check if current char is a digit
        else if(std::isdigit(b[i])) {
            // End of digit
            char* end;
            // Start of digit
            char* begin = b + i;
            double val;
            // Converts string to double
            val = strtod(begin, &end);
            // Increment i accordingly
            i = (end - b) - 1;
            // Add lexeme to back of tokens list
            tokens.push_back(lexeme(NUMBER, val));
            ++t;
        }
        else {
            // Switch current char to determine
            // which operator it is.
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
    // Prints the equation's tokens as a lexeme
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
}

/* precedence : lexeme -> int
 * precedence(tok) accepts a single parameter of type lexeme
 * and determines the level of precedence of tok.
 * Return - int
 * 
 * PRECEDENCE LEVEL (PEMDAS):
 * Addition       : + : Left  : 0
 * Subtraction    : - : Left  : 0
 * Multiplication : * : Left  : 1
 * Division       : / : Left  : 1
 * Exponentiation : ^ : Right : 2
 */
int precedence(lexeme tok){
    int precedence; // To be returned
    switch (tok.lex) 
    {
    // PLUS and MINUS = 0
    case PLUS:
    case MINUS:
        precedence = 0;
        break;
    // TIMES and DIVIDES = 1
    case TIMES:
    case DIVIDES:
        precedence = 1;
        break;
    // POWER = 2
    case POWER:
        precedence = 2;
        break;
    // Everything else = -1
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

/* association : token -> string
 * association(op) accepts a single parameter of type token
 * and determines if the token goes left or right.
 * Return - string
 */
string association(token op) {
    string left_to_right;
    switch(op) {
        // All ops (expcept POWER), numbers, and constants, go left
        case PLUS:
        case MINUS:
        case TIMES:
        case DIVIDES:
        case NUMBER:
        case PI:
        case E:
            left_to_right = "left";
            break;
        // POWER go right
        case POWER:
            left_to_right = "right";
            break;
        default:
            break;
    }
    return left_to_right;
}

/* op : lexeme -> bool
 * op(i) accepts a single parameter of type lexeme
 * and uses it to determine if it's token is an operator
 * or number.
 * Return - bool
 */
bool op(lexeme i)
{
    switch(i.lex)
    {
    // Operators
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVIDES:
    case POWER:
        return true;
    // Not an operator
    case LPAREN:
    case RPAREN:
    case NUMBER:
    case PI:
    case E:
        return false;
    }
    return false;
}

/* term : lexeme -> node*
 * term(tok) accepts a single parameter of type lexeme.
 * It then determines what type the lexeme is and creates
 * a node accordingly.
 * Return - node*
 */
struct node* term(lexeme tok) {
    struct node* n = new node();
    // Check if lexeme is a number
    if(tok.lex == NUMBER) {
        n->val = tok.value;
        n->type = Num;
        return n;
    }
    // Assign PI to lexeme
    else if(tok.lex == PI) {
        n->val = 3.14159265358979;
        n->type = Num;
        return n;
    }
    // Assign E to lexeme
    else if(tok.lex == E) {
        n->val = 2.71828182845904;
        n->type = Num;
        return n;
    }
    // Check if lexeme is a left paren
    else if(tok.lex == LPAREN) {
        n = expr(-1);
        // Check if lexeme is right paren
        if(tok.lex == RPAREN)
            return n;
    }
    else {
        // failure - expected number but got something else
    }
    return nullptr;
}

/* expr : int -> node*
 * expr(prev_precedence) builds a tree that holds the order
 * of operations for the evaluator to follow.
 * Return - node*
 */
struct node* expr(int prev_precendence) {
    struct node* n = new node();
    // Left hand side
    struct node* lhs = term(*tokens.begin());
    // Right hand side
    struct node* rhs = new node();

    while(tokens.size() > 0) {
        auto oper = tokens.begin();
        auto peek = oper;
        // Set iter oper to next element after erased element
        oper = tokens.erase(tokens.begin());
        // Check current precedence 
        int curr_precedence = precedence(*oper);
        if(curr_precedence < prev_precendence) { 
            tokens.insert(oper, *oper);
            break;
        }
        // Check if lexeme token is assoc with left
        if(association(oper->lex) == "left") 
            rhs = expr(curr_precedence+1);
        else
            rhs = expr(curr_precedence);

        // Assign left, right, and operator to node n
        n->expr.lhs = lhs;
        n->expr.rhs = rhs;
        n->expr.op = oper->lex;
        // Increment iter oper
        oper++;
    }
    // Return node n
    return n;
}

/* Evaluator : node* -> double
 * Evaluator(node) : Evaluates the node expression
 * Return - double
 */

double Evaluator(struct node* node)
{
    if(node->type == Expr) {
        double lhs = Evaluator(node->expr.lhs);
        double rhs = Evaluator(node->expr.rhs);

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
    }
    else {
        return node->val; // It's a NumberNode
    }
}

// 1+2*3-8/(3-1) = 3

