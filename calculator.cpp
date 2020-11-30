//Anthony Phillips and Trevor Bender
//CSCI 330: Calculator
//Dr. Killian
//December 6th, 2020

#include <iomanip>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

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
    string expression;
    cout << "Please enter an expression: ";
    cin >> expression;
    lexicalAnalyzer(expression);
    Parser();
    Evaluator();
}

void lexicalAnalyzer(string expression)
{
    int count = 0;
    const string number = "NUMBER(";
    const string paren = ")";
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
    int length = expression.length();
    expression[length];
    string lexemes[length];

    while(count < expression.size())
    {
        string operators[9] = {"+", "-", "*", "/", "^", "(", ")", "pi", "e"};
        string lexOp[9] = { "PLUS", "MINUS", "TIMES", "DIVIDES", "POWER", "LPAREN", "RPAREN", "PI", "E"};
        for(int j = 0; j < 9; j++)
        {
            if(operators[j] == std::to_string(count))
            {
                lexemes[count] = lexOp[j];
                break;
                cout << lexemes[count] << endl;
            }
        }
        count++;
    }
}

void Parser()
{

}

void Evaluator()
{

}