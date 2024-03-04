#include "inputparser.hpp"

inputparser::inputparser(std::string input) : current_char(' '), current_pos(-1)
{
    content = removeTrailingWhiteSpace(input);
    content += " \n";
    while(checkNextchar() != '\n') getNextToken();
}

std::string inputparser::removeTrailingWhiteSpace(const std::string input)
{
    for (int i = input.length() - 1; i > 0; i--)
    {
        if (input[i] != ' ')
        {
            std::string contentString = input.substr(0, i+1);
            return contentString;
        }
    }
    return "";
}

void inputparser::printStatus()
{
    for (std::string s : tokens) std::cout << s << std::endl;
}

char inputparser::checkNextchar()
{
    return content[current_pos+1];
}

char inputparser::checkPreviousChar()
{
    if (current_pos == 0) return ' ';
    return content[current_pos-1];
}

void inputparser::consumeChar()
{
    if (checkNextchar() == 0) return;
    current_pos++;
    current_char = content[current_pos];
}

bool inputparser::isNumber(char input)
{
    for (char i = '0'; i <= '9'; i++) if (input == i) return true;
    return false;
}

void inputparser::getNextToken()
{
    ignoreWhiteSpace();
    std::string tokenstring;
    if (((current_char == '-' || current_char == '+') && isNumber(checkNextchar()) && checkPreviousChar() == ' '))
    {
        size_t begin = current_pos;
        consumeChar();
        while((isNumber(current_char) || current_char == '.') && checkNextchar() != '\n') consumeChar();
        size_t length = current_pos - begin;
        tokenstring = content.substr(begin, length);
        if (length != 0) tokens.push_back(tokenstring);
    }
    else if (isNumber(current_char))
    {
        size_t begin = current_pos;
        while(isNumber(current_char) || current_char == '.' && checkNextchar() != '\n') consumeChar();
        size_t length = current_pos - begin;
        tokenstring = content.substr(begin, length);
        if (length != 0) tokens.push_back(tokenstring);
    }
    else switch (current_char)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '^':
            tokenstring.assign(1, current_char);
            tokens.push_back(tokenstring);
            consumeChar();
            break;
        default:
            std::cout << "Error: unknown character: " << current_char << std::endl;
            std::abort();
            break;
    }
}

void inputparser::ignoreWhiteSpace()
{
    while ((current_char == ' ' || current_char == '\t' || current_char == '\r') && checkNextchar() != '\n') consumeChar();
}