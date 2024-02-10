#pragma once
#include <string>
#include <iostream>
#include <vector>

class inputparser {
    std::string content;
    int current_pos;
    char current_char;
    char checkNextchar();
    char checkPreviousChar();
    void consumeChar();
    bool isNumber(char input);
    void getNextToken();
    void ignoreWhiteSpace();
    std::string removeTrailingWhiteSpace(const std::string input);

public:
    std::vector<std::string> tokens;
    inputparser(std::string input);
    void printStatus();
};