#include <algorithm>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <regex>

using std::cout;
using std::endl;
using std::string;

int main() {

    string input = "1 + 2";
    string output = std::regex_replace(input, std::regex("[^0-9]*([0-9]+).*"), string("$1"));

    cout << input << endl;
    cout << output << endl;

    return 0;
}