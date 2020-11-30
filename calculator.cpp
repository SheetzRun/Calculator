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

using std::string;
using std::cout;
using std::cin;
using std::endl;

/********** FUNCTION DEFINITIONS **********/

void Calculator();

void lexicalAnalyzer(string expression);

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
    // Get input expression from user
    string expression;
    cout << "Please enter an expression: ";
    std::getline(cin, expression);
    // Remove spaces from expression
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());

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

    string operators[7] = {"+", "-", "*", "/", "^", "(", ")"};
    string literals[3] = {"p", "i", "e"};
    string lexOp[9] = {"PLUS", "MINUS", "TIMES", "DIVIDES", "POWER", "LPAREN", "RPAREN", "PI", "E"};


    for(int i = 0; i < expression.length(); i++) {
        for(int k = 0; k < 7; k++) {
            // Does not trigger until final loop?
            if(operators[k] == expression.substr(i, 1)) {
                lexemes[i] = lexOp[k];
                break;
            }
        }
    }

    for(int i = 0; i < lexemes->length(); ++i) {
        cout << lexemes[i] << " ";
    }
    cout << endl;

    // while(count < expression.length())
    // {
        
    //     auto i = expression[count];
    //     for(int j = 0; j < 7; j++)
    //     {
    //         if(operators[j] == &i)
    //         {
    //             cout << lexOp[j];
    //             lexemes[count] = lexOp[j];
    //             // cout << lexemes << endl;
    //             // break;
    //         }
    //     }
    //     count++;
    // }
}

void Parser()
{

}

void Evaluator()
{

}

