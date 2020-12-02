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
        enum token tok;
        double value;
    };

    lexeme tokens[1024];

    string b[1024];
    scanf("%[a-z0-9]s", b);


    cout << strlen(b) << endl;

    int t = 0;
    for(int i = 0; i < strlen(b); i++) {
        cout << "LOOP" << endl;
        if(std::isblank(b[i])) {
            cout << "SPACE\n";
            continue;
        }
        else if(std::isalpha(b[i])) {

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
    }

    
    for(int i = 0; i < 10; i++) {
        cout << tokens[i].value << " ";
    }
    cout << endl;

    // for(auto i : tokens) cout << i.value << endl;

    return 0;
}