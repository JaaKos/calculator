#include <iostream>
#include <string>
#include "inputparser.hpp"
#include "calculator.hpp"

int main()
{
    std::string input;
    std::getline(std::cin, input);

    inputparser parser(input);
    calculator calc(parser.tokens);
    calc.printAnswers();
}