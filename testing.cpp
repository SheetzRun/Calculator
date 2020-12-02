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
using std::cout;
using std::cin;
using std::endl;
using std::string;


int main() {

    // int oc=0, cc=0, m;
    // char b[30], constants[30];
    // string operators[30];

    // cout << "enter the string: ";
    // scanf("%[^\n]s", b);

    // for(int i = 0; i < strlen(b); i++) {
    //     if(std::isspace(b[i])){
    //         continue;
    //     }
    //     else if(std::isdigit(b[i])) {
    //         m=(b[i]-'0');
    //         i=i+1;
    //         cout << "m before: " << m << endl;
    //         int power = 1;
    //         while(std::isdigit(b[i])) {
    //             cout << m << " : ";
    //             m = m*(pow(10, power))+(b[i]-'0');
    //             cout << m << endl;
    //             power++;
    //             i++;
    //         }
    //         i=i-1;
    //         constants[cc]=m;
    //         cout << m << endl;
    //         cc++;
    //     }
    //     else {
    //         if(b[i]=='*') {
    //             operators[oc] = "TIMES";
    //             oc++;
    //         }
    //         else if(b[i]=='-') {
    //             operators[oc] = "MINUS";
    //             oc++;
    //         }
    //         else if(b[i]=='+') {
    //             operators[oc] = "PLUS";
    //             oc++;
    //         }
    //         else if(b[i]=='/') {
    //             operators[oc] = "DIVIDES";
    //             oc++;
    //         }
    //         else if(b[i]=='^') {
    //             operators[oc] = "POWER";
    //             oc++;
    //         }
    //         else if(b[i]=='(') {
    //             operators[oc] = "LPAREN";
    //             oc++;
    //         }
    //         else if(b[i]==')') {
    //             operators[oc] = "RPAREN";
    //             oc++;
    //         }
    //     }
    // }

    // cout << "\noperators: ";
    // for(int i = 0; i < oc; i++) {
    //     cout << operators[i] << " ";
    // }

    // cout << "\nconstants: ";
    // for(int i = 0; i < cc; i++) {
    //     printf("%d ", constants[i]);
    // }


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

    char expr[1024];

    struct lexeme {
        token tok;
        double value;
    };

    lexeme tokens[1024];

    char b[1024];
    scanf("%[a-z0-9\\+\\-\\*\\/\\(\\)\\^ ]s", b);

    cout << strlen(b) << endl;

    int t = 0;
    for(int i = 0; i < strlen(b); i++) {
        cout << "i loop: " << i << endl;
        if(std::isblank(b[i])) {
            // Skip loop if is blank
            continue;
        }
        // else if(std::isalpha(b[i])) {
        //     switch(b[i]) {
        //         case 'p':
        //             if(b[i+1]=='i') tokens[t].tok = PI;
        //             i++;
        //             ++t;
        //             break;
        //         case 'i':
        //             break;
        //         case 'e':
        //             tokens[t].tok = E;
        //             ++t;
        //             break;
        //         default:
        //             cout << "Invalid input." << endl;
        //             break;
        //     }
        // }
        else if(b[i]=='p') {
            cout << "b[i+1]: " << b[i+1] << endl;
            if(b[i+1]=='i') {
                tokens[t].tok = PI;
                ++t;
                cout << "i: " << i << "; ";
                ++i;

                cout << i << endl;
            }
        }
        else if(b[i]=='e') {
            tokens[t].tok = E;
            ++t;
        }
        else if(std::isdigit(b[i])) {
            char* end;
            char* begin = b + i;
            double val;
            // Converts string to double
            val = strtod(begin, &end);
            i = (end - b) - 1;
            tokens[t].tok = NUMBER;
            tokens[t].value = val;
            ++t;
        }
        else {
            switch(b[i]) {
            case '+': 
                tokens[t].tok = PLUS;
                break;
            case '-': 
                tokens[t].tok = MINUS;
                break;
            case '*': 
                tokens[t].tok = TIMES;
                break;
            case '/': 
                tokens[t].tok = DIVIDES;
                break;
            case '^': 
                tokens[t].tok = POWER;
                break;
            case ')': 
                tokens[t].tok = RPAREN;
                break;
            case '(': 
                tokens[t].tok = LPAREN;
                break;
            }
            ++t;
        }
    }

    cout << "t: " << t << endl;
    
    for(int i = 0; i < t; i++) {
        switch(tokens[i].tok) {
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

    return 0;
}
