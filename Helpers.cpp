#include "Helpers.h"

std::vector<short> FindCharIndexes(const std::string& str)
{
    std::vector<short> indexes;
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == '|' && str[i - 1] == ' ')
        {
            indexes.push_back(i);
        }
    }
    return indexes;
}

void FillVec(std::vector<std::string>& vec, const std::string& str)
{
    int i0 = 0;
    for (int i = 0; i <= str.length(); ++i)
    {
        if ((str[i] == ' ') || (str[i] == '\0'))
        {
            if (i0 == i)
            {
                i0 = i + 1;
            }
            else
            {
                vec.push_back(str.substr(i0, i - i0));
                i0 = i + 1;
            }
        }
    }
}

bool IsDigitOrDot(char ch)
{
    if (std::isdigit(ch) || ch == '.')
    {
        return true;
    }
    return false;
}

bool IsStrDoub(const std::string& str)
{
    if (str[0] == '-')
    {
        if (str.length() > 1)
        {
            if (str[1] != '.')
            {
                for (int i = 1; i < str.length() - 1; ++i)
                {
                    if (!(IsDigitOrDot(str[i])))
                    {
                        return false;
                    }
                }
                if (!(std::isdigit(str[str.length() - 1])))
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if (std::isdigit(str[0]))
    {
        for (int i = 1; i < str.length() - 1; ++i)
        {
            if (!(IsDigitOrDot(str[i])))
            {
                return false;
            }
        }
        if (!(std::isdigit(str[str.length() - 1])))
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool IsStrEmpty(const std::string& str)
{
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

bool IsValidOperator(const std::string& str)
{
    if (str == "+" || str == "-" || str == "*" || str == "/")
    {
        return true;
    }
    return false;
}

bool IsValidCondition(const std::string& cond)
{
    if (cond == "M" || cond == "MH" || cond == "P" || cond == "PH" || cond == "H" || cond == "AH")
    {
        return true;
    }
    return false;
}

bool Cond(double num1, std::string cond, double num2)
{
    if (cond == "M") { return num1 > num2; }
    else if (cond == "MH") { return num1 >= num2; }
    else if (cond == "P") { return num1 < num2; }
    else if (cond == "PH") { return num1 <= num2; }
    else if (cond == "H") { return num1 == num2; }
    else if (cond == "AH") { return num1 != num2; }
}

double Calc(double num1, std::string oper, double num2)
{
    char op = oper[0];
    switch (op)
    {
    case '+':
        return num1 + num2;
        break;
    case '-':
        return num1 - num2;
        break;
    case '*':
        return num1 * num2;
        break;
    case '/':
        return num1 / num2;
        break;
    }
}

int VectorIncludes(const std::vector<KandV>& vec, const std::string& str)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i].key == str)
        {
            return i;
        }
    }
    return -1;
}

int VectorIncludes(const std::vector<std::string>& vec, const std::string& str)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == str)
        {
            return i;
            break;
        }
    }
    return -1;
}

bool IsPrintable(const std::vector<std::string>& vecstr, const std::vector<KandV>& vecint)
{
    if (vecstr.size() > 1)
    {
        if (vecstr[1][0] == '[' && (vecstr[vecstr.size() - 1][vecstr[vecstr.size() - 1].length() - 1] == ']') || (vecstr[1][0] == '[' && vecstr[vecstr.size() - 1].length() > 1 && (vecstr[vecstr.size() - 1].substr(vecstr[vecstr.size() - 1].length() - 2, 2) == "]:")))
        {
            return true;
        }
    }
    else
    {
        return false;
    }

    if (vecstr.size() == 2 && (vecstr[1].length() > 1))
    {
        if ((vecstr[1][0] == '{' && (vecstr[1][vecstr[1].length() - 1] == '}')) || (vecstr[1][0] == '{' && (vecstr[1].substr(vecstr[1].length() - 2, 2) == "}:")))
        {
            if (vecstr[1].substr(vecstr[1].length() - 2, 2) == "}:")
            {
                if (vecstr[1].length() == 3)
                {
                    return true;
                }
                else if (VectorIncludes(vecint, vecstr[1].substr(1, vecstr[1].length() - 3)) != -1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (vecstr[1][vecstr[1].length() - 1] == '}')
            {
                if (vecstr[1].length() == 2)
                {
                    return true;
                }
                else if (VectorIncludes(vecint, vecstr[1].substr(1, vecstr[1].length() - 2)) != -1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

        }
    }
    return false;
}