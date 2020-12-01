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

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

/********** FUNCTION DEFINITIONS **********/

void Calculator();

void lexicalAnalyzer(string expression);

void Parser();

void Evaluator();

int deleteElement(string arr[], int n, string x);

/********** MAIN **********/

int main()
{
    Calculator();
}

/********** FUNCTION IMPLEMENTATIONS **********/

void Calculator()
{
    // Get input expression from user
    string expression;
    cout << "Please enter an expression: ";
    std::getline(cin, expression);
    // Remove spaces from expression
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());

    cout << expression << endl;

    lexicalAnalyzer(expression);
    Parser();
    Evaluator();
}

void lexicalAnalyzer(string expression)
{

    int count = 0;
    const string number = "NUMBER(";
    const string paren = ")";
    int length = expression.length();
    string lexemes[length];
    vector<string> lex;

    string operators[7] = {"+", "-", "*", "/", "^", "(", ")"};
    string lexOp[9] = {"PLUS", "MINUS", "TIMES", "DIVIDES", "POWER", "LPAREN", "RPAREN", "PI", "E"};


    for(int i = 0; i < expression.length(); i++) {
        for(int k = 0; k < 7; k++) {
            // Does not trigger until final loop?
            if(operators[k] == expression.substr(i, 1)) {
                lexemes[i] = lexOp[k];
                break;
            }
        }

        for(int k = 0; k < 3; k++) {
            if(expression.substr(i, 2) == "pi") {
                lexemes[i] = "PI";
                break;
            }
            if(expression.substr(i, 1) == "e") {
                lexemes[i] = "E";
                break;
            }
        }
    }


    deleteElement(lexemes, sizeof(lexemes)/sizeof(lexemes[0]), "");

    for(auto i : lexemes) {
        lex.push_back(i);
    }

    lex.pop_back();

    for(auto i : lex) cout << i << " ";
    cout << endl;
}

void Parser()
{

}

void Evaluator()
{

}

int deleteElement(string arr[], int n, string x) {
    // Search for x in array
    int i;
    for(i = 0; i < n; i++) if(arr[i] == x) break;

    // If x found in array
    if(i < n) {
        // reduce size of array and move all
        // elements on space ahead
        n-=1;
        for(int j = i; j < n; j++) 
            arr[j] = arr[j+1];
    }
    return n;
}


