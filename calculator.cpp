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
#include <regex>

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
    // Parser();
    // Evaluator();
}

void lexicalAnalyzer(string expression)
{
    int count = 0;
    const string number = "NUMBER(";
    const string paren = ")";
    int length = expression.length();
    string lexemes[length];
    vector<string> lex;
    const std::regex numSearch("^[0-9]*[.]?[0-9]*$");
    const std::regex blankSearch("^.{0}$");
    string lexTemp = "";

    string operators[7] = {"+", "-", "*", "/", "^", "(", ")"};

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


    /*
        FIX WHEN FIRST EXPRESSION IS A NUMBER
        36 * 28.2 ---> NUMBER(36)

        EXPECTED
        NUMBER(36) TIMES NUMBER(28.2)
    */



    for(int i = 0; i < expression.length(); i++) {
        // Loop for operators
        for(int k = 0; k < 7; k++) {
            if(operators[k] == expression.substr(i, 1)) {
                lexTemp = lexOp[k];
                break;
            }
        }
        // Loop for PI and E constants
        for(int k = 0; k < 3; k++) {
            if(expression.substr(i, 2) == "pi") {
                lexTemp = "PI";
                break;
            }
            if(expression.substr(i, 1) == "e") {
                lexTemp = "E";
                break;
            }
        }
        // Loop for numbers
        int count = i;
        while(std::regex_match(expression.substr(count, 1), numSearch) && count < expression.length()) {
            lexTemp += expression.substr(count, 1);
            count++;
        }
        // Add formatting to any number
        if(!std::regex_match(lexTemp, blankSearch) && std::regex_match(lexTemp, numSearch)) lexTemp = number + lexTemp + paren;

        lexemes[i] = lexTemp;
        // Reset lexTemp
        lexTemp = "";
        // Jump i to value of count
        i = count;
    }


    // Remove all empty array elements
    int popCount = 0;
    for(auto i : lexemes) {
        if(i == "") popCount++;
        deleteElement(lexemes, sizeof(lexemes)/sizeof(lexemes[0]), "");
    }

    for(auto i : lexemes) {
        lex.push_back(i);
    }

    // Pop back vector until correct...
    for(int i = 0; i < popCount; i++) {
        lex.pop_back();
    }

    for(auto i : lex) cout << "[" << i << "]";
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
        return 1;
    }
    return 0;
}


