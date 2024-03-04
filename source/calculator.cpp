#include "calculator.hpp"


calculator::calculator(std::vector <std::string> input) : tokens(input)
{
    establishValue();
}

void calculator::establishValue()
{
    while (scanForBrackets()) tokens = handleBrackets(tokens);
    while (scanForOperations())
    {
        tokens = getResultsPowers(tokens);
        tokens = getResultsMulDiv(tokens);
        tokens = getResultsAddSub(tokens);
    }
    for (std::string token : tokens) answers.push_back(std::stod(token));
}

bool calculator::scanForBrackets()
{
    for (std::string token : tokens) if (token == "(") return true;
    return false;
}

bool calculator::scanForOperations()
{
    for (std::string token : tokens) if (token.length() == 1 && checkOperation(token[0])) return true;
    return false;
}

bool calculator::checkOperation(char input)
{
    for (char i : ALLOWED_OPERATORS) if (input == i) return true;
    return false;
}

std::vector <std::string> calculator::handleBrackets(std::vector <std::string>& source)
{
    bool insideBrackets = false;
    std::vector <std::string> tokenSublist;
    int subListbegin = 0;
    int subListend = 0;
    int i;
    for (i = 0; i < source.size(); i++)
    {
        if (source[i] == "(")
        {
            if (insideBrackets) tokenSublist.clear();
            insideBrackets = true;
            subListbegin = i;
            continue;
        }

        if (source[i] == ")" && insideBrackets)
        {
            insideBrackets = false;
            subListend = i;
            break;
        }

        if (insideBrackets)
        {
            tokenSublist.push_back(source[i]);
        }
    }
    for (int i = subListbegin; i < subListend; i++) source[i] = "deleted";
    while (tokenSublist.size() > 1)
    {
        //for (std::string token : tokenSublist) std::cout << token << " ";
        tokenSublist = getResultsPowers(tokenSublist);
        tokenSublist = getResultsMulDiv(tokenSublist);
        tokenSublist = getResultsAddSub(tokenSublist);
    }
    source[subListend] = tokenSublist[0];
    return cleanVector(source);
}

std::vector <std::string> calculator::cleanVector(std::vector <std::string>& source)
{
    std::vector <std::string> updatedTokens;
    for (std::string token : source)
    {
        if (token != "deleted") updatedTokens.push_back(token);
    }
    return updatedTokens;
}

std::vector <std::string> calculator::getResultsMulDiv(std::vector <std::string>& source)
{
    for (int i = 1; i < source.size(); i++)
    {
        if (source[i] == "*" || source[i] == "/")
        {
            double result, num1, num2;
            try
            {
                num1 = std::stod(source[i-1]);
                num2 = std::stod(source[i+1]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: Non-numeric value in calculation" << std::endl;
                std::abort();
            }

            if (source[i] == "*") result = num1 * num2;
            else if (source[i] == "/") result = num1 / num2;
            source[i-1] = "deleted";
            source[i] = "deleted";
            source[i+1] = std::to_string(result);
        }
    }
    return cleanVector(source);
}

std::vector <std::string> calculator::getResultsAddSub(std::vector <std::string>& source)
{

    for (int i = 1; i < source.size(); i++)
    {
        if (source[i] == "+" || source[i] == "-")
        {
            double result, num1, num2;
            try
            {
                num1 = std::stod(source[i-1]);
                num2 = std::stod(source[i+1]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: Non-numeric value in calculation" << std::endl;
                std::abort();
            }
            if (source[i] == "+") result = num1 + num2;
            else if (source[i] == "-") result = num1 - num2;
            source[i-1] = "deleted";
            source[i] = "deleted";
            source[i+1] = std::to_string(result);
        }
    }
    return cleanVector(source);
}

std::vector <std::string> calculator::getResultsPowers(std::vector <std::string>& source)
{

    for (int i = source.size() - 1; i >= 0; i--)
    {
        if (source[i] == "^")
        {
            double result, num1, num2;
            try
            {
                num1 = std::stod(source[i-1]);
                num2 = std::stod(source[i+1]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: Non-numeric value in calculation" << std::endl;
                std::abort();
            }
            result = std::pow(num1, num2);
            source[i+1] = "deleted";
            source[i] = "deleted";
            source[i-1] = std::to_string(result);
        }
    }
    return cleanVector(source);
}

void calculator::printStatus()
{
    for (std::string token : tokens) std::cout << token << " ";
    std::cout << std::endl;
}

void calculator::printAnswers() const
{
    for (double answer : answers) std::cout << answer << std::endl;
}