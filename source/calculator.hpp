#pragma once
#include <vector>
#include <string>
#include <iostream>

const char ALLOWED_OPERATORS[] = {'+', '-', '*', '/'};

class calculator {
    double finalAnswer;
    std::vector <std::string> tokens;
    std::vector <double> answers; 
    void establishValue();
    bool scanForBrackets();
    bool scanForOperations();
    bool checkOperation(char input);
    std::vector <std::string> getResultsMulDiv(std::vector <std::string>& source);
    std::vector <std::string> getResultsAddSub(std::vector <std::string>& source);
    std::vector <std::string> cleanVector(std::vector <std::string>& source);
    std::vector <std::string> handleBrackets(std::vector <std::string>& source);
public:
    calculator(std::vector <std::string> input);
    void printStatus();
    void printAnswers() const;
};