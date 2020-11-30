#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;

void removeSpaces(char);

int main() {

    string expression = "+ - * /";

    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());

    cout << expression << endl;    

    return 0;
}

void removeSpaces(char *str) {
    int count = 0;

    for(int i = 0; str[i]; i++) {
        if(str[i] != ' ') str[count++] = str[i];
    }
    str[count] = '\0';
}