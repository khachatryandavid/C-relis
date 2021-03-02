#include "Service.h"

void ProcessString(std::string& str)
{
    int pos = str.find('|');
    if (pos == 0)
    {
        str = "";
        return;
    }
    if (pos == std::string::npos)
    {
        while ((str.length() != 0) && (str[str.length() - 1] == ' '))
        {
            str = str.substr(0, str.length() - 1);
        }
        return;
    }
    else
    {
        std::vector<std::string> vec;
        FillVec(vec, str);
        if (vec[0] == "tpi")
        {
            vec.clear();
            vec.shrink_to_fit();
            std::vector<short> ind = FindCharIndexes(str);
            for (int i = 0; i < ind.size(); ++i)
            {
                if (str.find("}") != std::string::npos)
                {
                    if (str.find("}") < ind[i])
                    {
                        if (str.find("]") != std::string::npos)
                        {
                            if (str.find("]") < ind[i])
                            {
                                str = str.substr(0, ind[i]);
                                while ((str.length() != 0) && (str[str.length() - 1] == ' '))
                                {
                                    str = str.substr(0, str.length() - 1);
                                }
                                return;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        else
                        {
                            str = str.substr(0, ind[i]);
                            while ((str.length() != 0) && (str[str.length() - 1] == ' '))
                            {
                                str = str.substr(0, str.length() - 1);
                            }
                            return;
                        }
                    }
                    else
                    {
                        if (str.find("]") != std::string::npos)
                        {
                            if (str.find("]") < ind[i])
                            {
                                str = str.substr(0, ind[i]);
                                while ((str.length() != 0) && (str[str.length() - 1] == ' '))
                                {
                                    str = str.substr(0, str.length() - 1);
                                }
                                return;
                            }
                            else
                            {
                                if (str.find("[") != std::string::npos)
                                {
                                    if (str.find("[") > ind[i])
                                    {
                                        str = str.substr(0, ind[i]);
                                        while ((str.length() != 0) && (str[str.length() - 1] == ' '))
                                        {
                                            str = str.substr(0, str.length() - 1);
                                        }
                                        return;
                                    }
                                    else
                                    {
                                        continue;
                                    }
                                }
                                else
                                {
                                    str = str.substr(0, ind[i]);
                                    while ((str.length() != 0) && (str[str.length() - 1] == ' '))
                                    {
                                        str = str.substr(0, str.length() - 1);
                                    }
                                    return;
                                }
                            }

                        }
                    }
                }
                else if (str.find("]") != std::string::npos)
                {
                    if (str.find("]") < ind[i])
                    {
                        str = str.substr(0, ind[i]);
                        while ((str.length() != 0) && (str[str.length() - 1] == ' '))
                        {
                            str = str.substr(0, str.length() - 1);
                        }
                        return;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    str = str.substr(0, ind[i]);
                    while ((str.length() != 0) && (str[str.length() - 1] == ' '))
                    {
                        str = str.substr(0, str.length() - 1);
                    }
                    return;
                }
            }
            ind.clear();
            ind.shrink_to_fit();
        }
        else
        {
            vec.clear();
            vec.shrink_to_fit();
            if (str[pos - 1] == ' ')
            {
                str = str.substr(0, pos);
                while ((str.length() != 0) && (str[str.length() - 1] == ' '))
                {
                    str = str.substr(0, str.length() - 1);
                }
                return;
            }
        }
    }
    while ((str[str.length() - 1] == ' ') && str.length() != 0)
    {
        str = str.substr(0, str.length() - 1);
    }
}

int MoveToScope(std::ifstream& myfile, std::vector<KandV>& vecint, short& line)
{
    std::string str;
    while (getline(myfile, str))
    {
        if (IsStrEmpty(str))
        {
            ++line;
            continue;
        }
        ProcessString(str);
        if (IsStrEmpty(str))
        {
            ++line;
            continue;
        }
        if ((str[str.length() - 1] != '>'))
        {
            if (PureInterpret(str, vecint, line) == -1)
            {
                return -1;
            }
        }
        else
        {
            if (PureInterpret(str.substr(0, str.length() - 1), vecint, line) == -1)
            {
                return -1;
            }
            break;
        }
    }
    return 0;
}

void SkipUntilEndOfScope(std::ifstream& myfile, short& line)
{
    std::string str;
    while (getline(myfile, str))
    {
        ++line;
        if (IsStrEmpty(str))
        {
            continue;
        }
        ProcessString(str);
        if (IsStrEmpty(str))
        {
            continue;
        }
        if ((str[str.length() - 1] == '>'))
        {
            break;
        }
    }
}

int PureInterpret(std::string str, std::vector<KandV>& vecint, short& line)
{
    ++line;
    if (IsStrEmpty(str))
    {
        return 0;
    }
    ProcessString(str);
    if (IsStrEmpty(str))
    {
        return 0;
    }
    std::vector<std::string> vecstr;
    FillVec(vecstr, str);

    if (VectorIncludes(vecstr, "<-") != -1 && vecstr[0] != "tpi" && !(VectorIncludes(vecstr, "xosqi") == 0 && VectorIncludes(vecstr, "yete") == 1) && !(VectorIncludes(vecstr, "mti") == 0 && VectorIncludes(vecstr, "fra") == 1))
    {
        if (VectorIncludes(vecstr, "<-") == 2)
        {
            if (VectorIncludes(vecstr, "tiv") == 0)
            {
                if (vecstr[1] != "tiv")
                {
                    if (isalpha(vecstr[1][0]))
                    {
                        if (VectorIncludes(vecint, vecstr[1]) == -1)
                        {
                            if (vecstr.size() == 4)
                            {
                                if (IsStrDoub(vecstr[3]))
                                {
                                    vecint.push_back({ vecstr[1], std::stod(vecstr[3]) });
                                }
                                else if (VectorIncludes(vecint, vecstr[3]) != -1)
                                {
                                    vecint.push_back({ vecstr[1], vecint[VectorIncludes(vecint, vecstr[3])].value });
                                }
                                else
                                {
                                    std::cout << "\nLine " << line << ": Error! Only numbers or values of declared variables can be assigned to your variable!\n";
                                    return -1;
                                }
                            }
                            else if (vecstr.size() == 6)
                            {
                                if ((IsStrDoub(vecstr[3]) || (VectorIncludes(vecint, vecstr[3]) != -1)) &&
                                    IsStrDoub(vecstr[5]) || (VectorIncludes(vecint, vecstr[5]) != -1))
                                {
                                    if (IsValidOperator(vecstr[4]))
                                    {
                                        if (IsStrDoub(vecstr[3]))
                                        {
                                            if (IsStrDoub(vecstr[5]))
                                            {
                                                if (vecstr[4] == "/" && std::stod(vecstr[5]) == 0)
                                                {
                                                    std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                                    return -1;
                                                }
                                                vecint.push_back({ vecstr[1], Calc(std::stod(vecstr[3]), vecstr[4], std::stod(vecstr[5])) });
                                            }
                                            else
                                            {
                                                if (vecstr[4] == "/" && (vecint[VectorIncludes(vecint, vecstr[5])].value) == 0)
                                                {
                                                    std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                                    return -1;
                                                }
                                                vecint.push_back({ vecstr[1], Calc(std::stod(vecstr[3]), vecstr[4], (vecint[VectorIncludes(vecint, vecstr[5])].value)) });
                                            }
                                        }
                                        else
                                        {
                                            if (IsStrDoub(vecstr[5]))
                                            {
                                                if (vecstr[4] == "/" && std::stod(vecstr[5]) == 0)
                                                {
                                                    std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                                    return -1;
                                                }
                                                vecint.push_back({ vecstr[1], Calc((vecint[VectorIncludes(vecint, vecstr[3])].value), vecstr[4], std::stod(vecstr[5])) });
                                            }
                                            else
                                            {
                                                if (vecstr[4] == "/" && (vecint[VectorIncludes(vecint, vecstr[5])].value) == 0)
                                                {
                                                    std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                                    return -1;
                                                }
                                                vecint.push_back({ vecstr[1], Calc((vecint[VectorIncludes(vecint, vecstr[3])].value), vecstr[4], (vecint[VectorIncludes(vecint, vecstr[5])].value)) });
                                            }
                                        }
                                    }
                                    else
                                    {
                                        std::cout << "\nLine " << line << ": Error! Wrong operator! Use \"+\", \"-\", \"*\" or \"/\"!\n";
                                        return -1;
                                    }
                                }
                                else
                                {
                                    std::cout << "\nLine " << line << ": Error! Only numbers or values of declared variables can be assigned to your variable!\n";
                                    return -1;
                                }
                            }
                            else
                            {
                                std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                                return -1;
                            }
                        }
                        else
                        {
                            std::cout << "\nLine " << line << ": Error! A variable with name \"" << vecint[VectorIncludes(vecint, vecstr[1])].key << "\" already exists. Try another one!\n";
                            return -1;
                        }
                    }
                    else
                    {
                        std::cout << "\nLine " << line << ": Error! The name of a variable must begin with a letter. Try another name!\n";
                        return -1;
                    }
                }
                else
                {
                    std::cout << "\nLine " << line << ": Error! Can't declare a variable with name \"tiv\". Try another name!\n";
                    return -1;
                }
            }
            else
            {
                std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                return -1;
            }
        }
        else if (VectorIncludes(vecstr, "<-") == 1 && vecstr[0] != "tiv")
        {
            if (VectorIncludes(vecint, vecstr[0]) != -1)
            {
                if (vecstr.size() == 3)
                {
                    if (IsStrDoub(vecstr[2]))
                    {
                        vecint[VectorIncludes(vecint, vecstr[0])].value = std::stod(vecstr[2]);
                    }
                    else if (VectorIncludes(vecint, vecstr[2]) != -1)
                    {
                        vecint[VectorIncludes(vecint, vecstr[0])].value = vecint[VectorIncludes(vecint, vecstr[2])].value;
                    }
                    else
                    {
                        std::cout << "\nLine " << line << ": Error! Only numbers or values of declared variables can be assigned to your variable!\n";
                        return -1;
                    }
                }
                else if (vecstr.size() == 5)
                {
                    if ((IsStrDoub(vecstr[2]) || (VectorIncludes(vecint, vecstr[2]) != -1)) &&
                        IsStrDoub(vecstr[4]) || (VectorIncludes(vecint, vecstr[4]) != -1))
                    {
                        if (IsValidOperator(vecstr[3]))
                        {
                            if (IsStrDoub(vecstr[2]))
                            {
                                if (IsStrDoub(vecstr[4]))
                                {
                                    if (vecstr[3] == "/" && std::stod(vecstr[4]) == 0)
                                    {
                                        std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                        return -1;
                                    }
                                    vecint[VectorIncludes(vecint, vecstr[0])].value = Calc(std::stod(vecstr[2]), vecstr[3], std::stod(vecstr[4]));
                                }
                                else
                                {
                                    if (vecstr[3] == "/" && (vecint[VectorIncludes(vecint, vecstr[4])].value) == 0)
                                    {
                                        std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                        return -1;
                                    }
                                    vecint[VectorIncludes(vecint, vecstr[0])].value = Calc(std::stod(vecstr[2]), vecstr[3], (vecint[VectorIncludes(vecint, vecstr[4])].value));
                                }
                            }
                            else
                            {
                                if (IsStrDoub(vecstr[4]))
                                {
                                    if (vecstr[3] == "/" && std::stod(vecstr[4]) == 0)
                                    {
                                        std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                        return -1;
                                    }
                                    vecint[VectorIncludes(vecint, vecstr[0])].value = Calc((vecint[VectorIncludes(vecint, vecstr[2])].value), vecstr[3], std::stod(vecstr[4]));
                                }
                                else
                                {
                                    if (vecstr[3] == "/" && (vecint[VectorIncludes(vecint, vecstr[4])].value) == 0)
                                    {
                                        std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                        return -1;
                                    }
                                    vecint[VectorIncludes(vecint, vecstr[0])].value = Calc((vecint[VectorIncludes(vecint, vecstr[2])].value), vecstr[3], (vecint[VectorIncludes(vecint, vecstr[4])].value));
                                }
                            }
                        }
                        else
                        {
                            std::cout << "\nLine " << line << ": Error! Wrong operator! Use \"+\", \"-\", \"*\" or \"/\"!\n";
                            return -1;
                        }
                    }
                    else
                    {
                        std::cout << "\nLine " << line << ": Error! Only numbers or values of declared variables can be assigned to your variable!\n";
                        return -1;
                    }
                }
                else
                {
                    std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                    return -1;
                }
            }
            else
            {
                std::cout << "\nLine " << line << ": Error! Undeclared variable!\n";
                return -1;
            }
        }
        else
        {
            std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
            return -1;
        }
    }
    else if (VectorIncludes(vecstr, "tiv") == 0)
    {
        if (vecstr.size() == 1)
        {
            std::cout << "\nLine " << line << ": Error! Can't declare a variable without a name!\n";
            return -1;
        }
        if (vecstr.size() == 2)
        {
            if (vecstr[1] != "tiv")
            {
                if (isalpha(vecstr[1][0]))
                {
                    if (VectorIncludes(vecint, vecstr[1]) == -1)
                    {
                        vecint.push_back({ vecstr[1], 0 });
                    }
                    else
                    {
                        std::cout << "\nLine " << line << ": Error! A variable with name \"" << vecint[VectorIncludes(vecint, vecstr[1])].key << "\" already exists. Try another one!\n";
                        return -1;
                    }
                }
                else
                {
                    std::cout << "\nLine " << line << ": Error! The name of a variable must begin with a letter. Try another name!\n";
                    return -1;
                }
            }
            else
            {
                std::cout << "\nLine " << line << ": Error! Can't declare a variable with name \"tiv\". Try another name!\n";
                return -1;
            }
        }
        else
        {
            std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
            return -1;
        }
    }
    else if (vecstr[0] == "tpi")
    {
        if (IsPrintable(vecstr, vecint))
        {
            if (vecstr[vecstr.size() - 1][vecstr[vecstr.size() - 1].length() - 1] == ']')
            {
                std::cout << str.substr(str.find('[') + 1, str.length() - str.find('[') - 2);
            }
            else if (vecstr[vecstr.size() - 1].substr(vecstr[vecstr.size() - 1].length() - 2, 2) == "]:")
            {
                std::cout << str.substr(str.find('[') + 1, str.length() - str.find('[') - 3) << std::endl;
            }
            else if (vecstr[1][vecstr[1].length() - 1] == '}')
            {
                if (vecstr[1].length() == 2)
                {
                    std::cout << "";
                }
                else
                {
                    std::cout << vecint[VectorIncludes(vecint, vecstr[1].substr(1, vecstr[1].length() - 2))].value;
                }
            }
            else if (vecstr[1].substr(vecstr[1].length() - 2, 2) == "}:")
            {
                if (vecstr[1].length() == 3)
                {
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << vecint[VectorIncludes(vecint, vecstr[1].substr(1, vecstr[1].length() - 3))].value << std::endl;
                }
            }
        }
        else
        {
            std::cout << "\nLine " << line << ": Error! Can't print! Wrong parenthesis or undeclared variables!\n";
            return -1;
        }
    }
    else if (VectorIncludes(vecstr, "xosqi") == 0 && VectorIncludes(vecstr, "yete") == 1)
    {
        std::cout << "\nLine " << line << ": Error! Can't use Loops or Conditional statements in scopes!\n";
        return -1;
    }
    else if (VectorIncludes(vecstr, "mti") == 0 && VectorIncludes(vecstr, "fra") == 1)
    {
        std::cout << "\nLine " << line << ": Error! Can't use Loops or Conditional statements in scopes!\n";
        return -1;
    }
    else
    {
        std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
        return -1;
    }
    vecstr.clear();
    vecstr.shrink_to_fit();
    return 0;
}

std::vector<std::string> CreateLoopScope(std::ifstream& myfile)
{
    std::string str;
    std::vector<std::string> vecline;
    while (getline(myfile, str))
    {
        if (IsStrEmpty(str))
        {
            vecline.push_back("");
            continue;
        }
        ProcessString(str);
        if (IsStrEmpty(str))
        {
            vecline.push_back("");
            continue;
        }
        if ((str[str.length() - 1] != '>'))
        {
            vecline.push_back(str);
        }
        else
        {
            vecline.push_back(str.substr(0, str.length() - 1));
            break;
        }
    }
    return vecline;
}

int InterpretLoopScope(const std::vector<std::string>& vecline, std::vector<KandV>& vecint, short& line)
{
    for (int i = 0; i < vecline.size(); ++i)
    {
        if (PureInterpret(vecline[i], vecint, line) == -1)
        {
            return -1;
        }
    }
    return 0;
}

int InterpretC_relis(std::ifstream& myfile)
{
    short line = 0;
    std::string str;
    std::vector<std::string> vecstr;
    std::vector<KandV> vecint;
    while (!myfile.eof())
    {
        getline(myfile, str);
        ++line;
        if (IsStrEmpty(str))
        {
            continue;
        }
        ProcessString(str);
        if (IsStrEmpty(str))
        {
            continue;
        }
        FillVec(vecstr, str);

        if (VectorIncludes(vecstr, "<-") != -1 && vecstr[0] != "tpi" && !(VectorIncludes(vecstr, "xosqi") == 0 && VectorIncludes(vecstr, "yete") == 1) && !(VectorIncludes(vecstr, "mti") == 0 && VectorIncludes(vecstr, "fra") == 1))
        {
            if (VectorIncludes(vecstr, "<-") == 2)
            {
                if (VectorIncludes(vecstr, "tiv") == 0)
                {
                    if (vecstr[1] != "tiv")
                    {
                        if (isalpha(vecstr[1][0]))
                        {
                            if (VectorIncludes(vecint, vecstr[1]) == -1)
                            {
                                if (vecstr.size() == 4)
                                {
                                    if (IsStrDoub(vecstr[3]))
                                    {
                                        vecint.push_back({ vecstr[1], std::stod(vecstr[3]) });
                                    }
                                    else if (VectorIncludes(vecint, vecstr[3]) != -1)
                                    {
                                        vecint.push_back({ vecstr[1], vecint[VectorIncludes(vecint, vecstr[3])].value });
                                    }
                                    else
                                    {
                                        std::cout << "\nLine " << line << ": Error! Only numbers or values of declared variables can be assigned to your variable!\n";
                                        return -1;
                                    }
                                }
                                else if (vecstr.size() == 6)
                                {
                                    if ((IsStrDoub(vecstr[3]) || (VectorIncludes(vecint, vecstr[3]) != -1)) &&
                                        IsStrDoub(vecstr[5]) || (VectorIncludes(vecint, vecstr[5]) != -1))
                                    {
                                        if (IsValidOperator(vecstr[4]))
                                        {
                                            if (IsStrDoub(vecstr[3]))
                                            {
                                                if (IsStrDoub(vecstr[5]))
                                                {
                                                    if (vecstr[4] == "/" && std::stod(vecstr[5]) == 0)
                                                    {
                                                        std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                                        return -1;
                                                    }
                                                    vecint.push_back({ vecstr[1], Calc(std::stod(vecstr[3]), vecstr[4], std::stod(vecstr[5])) });
                                                }
                                                else
                                                {
                                                    if (vecstr[4] == "/" && (vecint[VectorIncludes(vecint, vecstr[5])].value) == 0)
                                                    {
                                                        std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                                        return -1;
                                                    }
                                                    vecint.push_back({ vecstr[1], Calc(std::stod(vecstr[3]), vecstr[4], (vecint[VectorIncludes(vecint, vecstr[5])].value)) });
                                                }
                                            }
                                            else
                                            {
                                                if (IsStrDoub(vecstr[5]))
                                                {
                                                    if (vecstr[4] == "/" && std::stod(vecstr[5]) == 0)
                                                    {
                                                        std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                                        return -1;
                                                    }
                                                    vecint.push_back({ vecstr[1], Calc((vecint[VectorIncludes(vecint, vecstr[3])].value), vecstr[4], std::stod(vecstr[5])) });
                                                }
                                                else
                                                {
                                                    if (vecstr[4] == "/" && (vecint[VectorIncludes(vecint, vecstr[5])].value) == 0)
                                                    {
                                                        std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                                        return -1;
                                                    }
                                                    vecint.push_back({ vecstr[1], Calc((vecint[VectorIncludes(vecint, vecstr[3])].value), vecstr[4], (vecint[VectorIncludes(vecint, vecstr[5])].value)) });
                                                }
                                            }
                                        }
                                        else
                                        {
                                            std::cout << "\nLine " << line << ": Error! Wrong operator! Use \"+\", \"-\", \"*\" or \"/\"!\n";
                                            return -1;
                                        }
                                    }
                                    else
                                    {
                                        std::cout << "\nLine " << line << ": Error! Only numbers or values of declared variables can be assigned to your variable!\n";
                                        return -1;
                                    }
                                }
                                else
                                {
                                    std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                                    return -1;
                                }
                            }
                            else
                            {
                                std::cout << "\nLine " << line << ": Error! A variable with name \"" << vecint[VectorIncludes(vecint, vecstr[1])].key << "\" already exists. Try another one!\n";
                                return -1;
                            }
                        }
                        else
                        {
                            std::cout << "\nLine " << line << ": Error! The name of a variable must begin with a letter. Try another name!\n";
                            return -1;
                        }
                    }
                    else
                    {
                        std::cout << "\nLine " << line << ": Error! Can't declare a variable with name \"tiv\". Try another name!\n";
                        return -1;
                    }
                }
                else
                {
                    std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                    return -1;
                }
            }
            else if (VectorIncludes(vecstr, "<-") == 1 && vecstr[0] != "tiv")
            {
                if (VectorIncludes(vecint, vecstr[0]) != -1)
                {
                    if (vecstr.size() == 3)
                    {
                        if (IsStrDoub(vecstr[2]))
                        {
                            vecint[VectorIncludes(vecint, vecstr[0])].value = std::stod(vecstr[2]);
                        }
                        else if (VectorIncludes(vecint, vecstr[2]) != -1)
                        {
                            vecint[VectorIncludes(vecint, vecstr[0])].value = vecint[VectorIncludes(vecint, vecstr[2])].value;
                        }
                        else
                        {
                            std::cout << "\nLine " << line << ": Error! Only numbers or values of declared variables can be assigned to your variable!\n";
                            return -1;
                        }
                    }
                    else if (vecstr.size() == 5)
                    {
                        if ((IsStrDoub(vecstr[2]) || (VectorIncludes(vecint, vecstr[2]) != -1)) &&
                            IsStrDoub(vecstr[4]) || (VectorIncludes(vecint, vecstr[4]) != -1))
                        {
                            if (IsValidOperator(vecstr[3]))
                            {
                                if (IsStrDoub(vecstr[2]))
                                {
                                    if (IsStrDoub(vecstr[4]))
                                    {
                                        if (vecstr[3] == "/" && std::stod(vecstr[4]) == 0)
                                        {
                                            std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                            return -1;
                                        }
                                        vecint[VectorIncludes(vecint, vecstr[0])].value = Calc(std::stod(vecstr[2]), vecstr[3], std::stod(vecstr[4]));
                                    }
                                    else
                                    {
                                        if (vecstr[3] == "/" && (vecint[VectorIncludes(vecint, vecstr[4])].value) == 0)
                                        {
                                            std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                            return -1;
                                        }
                                        vecint[VectorIncludes(vecint, vecstr[0])].value = Calc(std::stod(vecstr[2]), vecstr[3], (vecint[VectorIncludes(vecint, vecstr[4])].value));
                                    }
                                }
                                else
                                {
                                    if (IsStrDoub(vecstr[4]))
                                    {
                                        if (vecstr[3] == "/" && std::stod(vecstr[4]) == 0)
                                        {
                                            std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                            return -1;
                                        }
                                        vecint[VectorIncludes(vecint, vecstr[0])].value = Calc((vecint[VectorIncludes(vecint, vecstr[2])].value), vecstr[3], std::stod(vecstr[4]));
                                    }
                                    else
                                    {
                                        if (vecstr[3] == "/" && (vecint[VectorIncludes(vecint, vecstr[4])].value) == 0)
                                        {
                                            std::cout << "\nLine " << line << ": Error! Can't divide to 0!\n";
                                            return -1;
                                        }
                                        vecint[VectorIncludes(vecint, vecstr[0])].value = Calc((vecint[VectorIncludes(vecint, vecstr[2])].value), vecstr[3], (vecint[VectorIncludes(vecint, vecstr[4])].value));
                                    }
                                }
                            }
                            else
                            {
                                std::cout << "\nLine " << line << ": Error! Wrong operator! Use \"+\", \"-\", \"*\" or \"/\"!\n";
                                return -1;
                            }
                        }
                        else
                        {
                            std::cout << "\nLine " << line << ": Error! Only numbers or values of declared variables can be assigned to your variable!\n";
                            return -1;
                        }
                    }
                    else
                    {
                        std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                        return -1;
                    }
                }
                else
                {
                    std::cout << "\nLine " << line << ": Error! Undeclared variable!\n";
                    return -1;
                }
            }
            else
            {
                std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                return -1;
            }
        }
        else if (VectorIncludes(vecstr, "tiv") == 0)
        {
            if (vecstr.size() == 1)
            {
                std::cout << "\nLine " << line << ": Error! Can't declare a variable without a name!\n";
                return -1;
            }
            if (vecstr.size() == 2)
            {
                if (vecstr[1] != "tiv")
                {
                    if (isalpha(vecstr[1][0]))
                    {
                        if (VectorIncludes(vecint, vecstr[1]) == -1)
                        {
                            vecint.push_back({ vecstr[1], 0 });
                        }
                        else
                        {
                            std::cout << "\nLine " << line << ": Error! A variable with name \"" << vecint[VectorIncludes(vecint, vecstr[1])].key << "\" already exists. Try another one!\n";
                            return -1;
                        }
                    }
                    else
                    {
                        std::cout << "\nLine " << line << ": Error! The name of a variable must begin with a letter. Try another name!\n";
                        return -1;
                    }
                }
                else
                {
                    std::cout << "\nLine " << line << ": Error! Can't declare a variable with name \"tiv\". Try another name!\n";
                    return -1;
                }
            }
            else
            {
                std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                return -1;
            }
        }
        else if (vecstr[0] == "tpi")
        {
            if (IsPrintable(vecstr, vecint))
            {
                if (vecstr[vecstr.size() - 1][vecstr[vecstr.size() - 1].length() - 1] == ']')
                {
                    std::cout << str.substr(str.find('[') + 1, str.length() - str.find('[') - 2);
                }
                else if (vecstr[vecstr.size() - 1].substr(vecstr[vecstr.size() - 1].length() - 2, 2) == "]:")
                {
                    std::cout << str.substr(str.find('[') + 1, str.length() - str.find('[') - 3) << std::endl;
                }
                else if (vecstr[1][vecstr[1].length() - 1] == '}')
                {
                    if (vecstr[1].length() == 2)
                    {
                        std::cout << "";
                    }
                    else
                    {
                        std::cout << vecint[VectorIncludes(vecint, vecstr[1].substr(1, vecstr[1].length() - 2))].value;
                    }
                }
                else if (vecstr[1].substr(vecstr[1].length() - 2, 2) == "}:")
                {
                    if (vecstr[1].length() == 3)
                    {
                        std::cout << std::endl;
                    }
                    else
                    {
                        std::cout << vecint[VectorIncludes(vecint, vecstr[1].substr(1, vecstr[1].length() - 3))].value << std::endl;
                    }
                }
            }
            else
            {
                std::cout << "\nLine " << line << ": Error! Can't print! Wrong parenthesis or undeclared variables!\n";
                return -1;
            }
        }
        else if (VectorIncludes(vecstr, "xosqi") == 0 && VectorIncludes(vecstr, "yete") == 1)
        {
            if (vecstr.size() == 5)
            {
                if (IsValidCondition(vecstr[3]))
                {
                    if (vecstr[2][0] == '[' && vecstr[4][vecstr[4].length() - 1] == ']')
                    {
                        if ((IsStrDoub(vecstr[2].substr(1, vecstr[2].length() - 1)) || \
                            (VectorIncludes(vecint, vecstr[2].substr(1, vecstr[2].length() - 1)) != -1)) && \
                            IsStrDoub(vecstr[4].substr(0, vecstr[4].length() - 1)) || \
                            (VectorIncludes(vecint, vecstr[4].substr(0, vecstr[4].length() - 1)) != -1))
                        {
                            if (IsStrDoub(vecstr[2].substr(1, vecstr[2].length() - 1)))
                            {
                                if (IsStrDoub(vecstr[4].substr(0, vecstr[4].length() - 1)))
                                {
                                    if (Cond(std::stod(vecstr[2].substr(1, vecstr[2].length() - 1)), \
                                        vecstr[3], std::stod(vecstr[4].substr(0, vecstr[4].length() - 1))))
                                    {
                                        if (MoveToScope(myfile, vecint, line) == -1)
                                        {
                                            return -1;
                                        }
                                    }
                                    else
                                    {
                                        SkipUntilEndOfScope(myfile, line);
                                    }
                                }
                                else
                                {
                                    if (Cond(std::stod(vecstr[2].substr(1, vecstr[2].length() - 1)), \
                                        vecstr[3], vecint[VectorIncludes(vecint, vecstr[4].substr(0, vecstr[4].length() - 1))].value))
                                    {
                                        if (MoveToScope(myfile, vecint, line) == -1)
                                        {
                                            return -1;
                                        }
                                    }
                                    else
                                    {
                                        SkipUntilEndOfScope(myfile, line);
                                    }
                                }
                            }
                            else
                            {
                                if (IsStrDoub(vecstr[4].substr(0, vecstr[4].length() - 1)))
                                {
                                    if (Cond(vecint[VectorIncludes(vecint, vecstr[2].substr(1, vecstr[2].length() - 1))].value, \
                                        vecstr[3], std::stod(vecstr[4].substr(0, vecstr[4].length() - 1))))
                                    {
                                        if (MoveToScope(myfile, vecint, line) == -1)
                                        {
                                            return -1;
                                        }
                                    }
                                    else
                                    {
                                        SkipUntilEndOfScope(myfile, line);
                                    }
                                }
                                else
                                {
                                    if (Cond(vecint[VectorIncludes(vecint, vecstr[2].substr(1, vecstr[2].length() - 1))].value, \
                                        vecstr[3], vecint[VectorIncludes(vecint, vecstr[4].substr(0, vecstr[4].length() - 1))].value))
                                    {
                                        if (MoveToScope(myfile, vecint, line) == -1)
                                        {
                                            return -1;
                                        }
                                    }
                                    else
                                    {
                                        SkipUntilEndOfScope(myfile, line);
                                    }
                                }
                            }
                        }
                        else
                        {
                            std::cout << "\nLine " << line << ": Error! Invalid condition! Use numbers or declared variables!\n";
                            return -1;
                        }
                    }
                    else
                    {
                        std::cout << "\nLine " << line << ": Error! Invalid condition! Check square brackets!\n";
                        return -1;
                    }
                }
                else
                {
                    std::cout << "\nLine " << line << ": Error! Invalid condition! Use \"M\", \"MH\", \"P\", \"PH\", \"H\" or \"AH\"!\n";
                    return -1;
                }
            }
            else
            {
                std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                return -1;
            }

        }
        else if (VectorIncludes(vecstr, "mti") == 0 && VectorIncludes(vecstr, "fra") == 1)
        {
            if (vecstr.size() == 5)
            {
                if (IsValidCondition(vecstr[3]))
                {
                    if (vecstr[2][0] == '[' && vecstr[4][vecstr[4].length() - 1] == ']')
                    {
                        if ((IsStrDoub(vecstr[2].substr(1, vecstr[2].length() - 1)) || \
                            (VectorIncludes(vecint, vecstr[2].substr(1, vecstr[2].length() - 1)) != -1)) && \
                            IsStrDoub(vecstr[4].substr(0, vecstr[4].length() - 1)) || \
                            (VectorIncludes(vecint, vecstr[4].substr(0, vecstr[4].length() - 1)) != -1))
                        {
                            if (IsStrDoub(vecstr[2].substr(1, vecstr[2].length() - 1)))
                            {
                                if (IsStrDoub(vecstr[4].substr(0, vecstr[4].length() - 1)))
                                {
                                    if (Cond(std::stod(vecstr[2].substr(1, vecstr[2].length() - 1)), \
                                        vecstr[3], std::stod(vecstr[4].substr(0, vecstr[4].length() - 1))))
                                    {
                                        std::vector<std::string> tmp = CreateLoopScope(myfile);
                                        short temp = line;
                                        while (Cond(std::stod(vecstr[2].substr(1, vecstr[2].length() - 1)), \
                                            vecstr[3], std::stod(vecstr[4].substr(0, vecstr[4].length() - 1))))
                                        {
                                            line = temp;
                                            if (InterpretLoopScope(tmp, vecint, line) == -1)
                                            {
                                                return -1;
                                            }
                                        }
                                        tmp.clear();
                                        tmp.shrink_to_fit();
                                    }
                                    else
                                    {
                                        SkipUntilEndOfScope(myfile, line);
                                    }
                                }
                                else
                                {
                                    if (Cond(std::stod(vecstr[2].substr(1, vecstr[2].length() - 1)), \
                                        vecstr[3], vecint[VectorIncludes(vecint, vecstr[4].substr(0, vecstr[4].length() - 1))].value))
                                    {
                                        std::vector<std::string> tmp = CreateLoopScope(myfile);
                                        short temp = line;
                                        while (Cond(std::stod(vecstr[2].substr(1, vecstr[2].length() - 1)), \
                                            vecstr[3], vecint[VectorIncludes(vecint, vecstr[4].substr(0, vecstr[4].length() - 1))].value))
                                        {
                                            line = temp;
                                            if (InterpretLoopScope(tmp, vecint, line) == -1)
                                            {
                                                return -1;
                                            }
                                        }
                                        tmp.clear();
                                        tmp.shrink_to_fit();
                                    }
                                    else
                                    {
                                        SkipUntilEndOfScope(myfile, line);
                                    }
                                }
                            }
                            else
                            {
                                if (IsStrDoub(vecstr[4].substr(0, vecstr[4].length() - 1)))
                                {
                                    if (Cond(vecint[VectorIncludes(vecint, vecstr[2].substr(1, vecstr[2].length() - 1))].value, \
                                        vecstr[3], std::stod(vecstr[4].substr(0, vecstr[4].length() - 1))))
                                    {
                                        std::vector<std::string> tmp = CreateLoopScope(myfile);
                                        short temp = line;
                                        while (Cond(vecint[VectorIncludes(vecint, vecstr[2].substr(1, vecstr[2].length() - 1))].value, \
                                            vecstr[3], std::stod(vecstr[4].substr(0, vecstr[4].length() - 1))))
                                        {
                                            line = temp;
                                            if (InterpretLoopScope(tmp, vecint, line) == -1)
                                            {
                                                return -1;
                                            }
                                        }
                                        tmp.clear();
                                        tmp.shrink_to_fit();
                                    }
                                    else
                                    {
                                        SkipUntilEndOfScope(myfile, line);
                                    }
                                }
                                else
                                {
                                    if (Cond(vecint[VectorIncludes(vecint, vecstr[2].substr(1, vecstr[2].length() - 1))].value, \
                                        vecstr[3], vecint[VectorIncludes(vecint, vecstr[4].substr(0, vecstr[4].length() - 1))].value))
                                    {
                                        std::vector<std::string> tmp = CreateLoopScope(myfile);
                                        short temp = line;
                                        while (Cond(vecint[VectorIncludes(vecint, vecstr[2].substr(1, vecstr[2].length() - 1))].value, \
                                            vecstr[3], vecint[VectorIncludes(vecint, vecstr[4].substr(0, vecstr[4].length() - 1))].value))
                                        {
                                            line = temp;
                                            if (InterpretLoopScope(tmp, vecint, line) == -1)
                                            {
                                                return -1;
                                            }
                                        }
                                        tmp.clear();
                                        tmp.shrink_to_fit();
                                    }
                                    else
                                    {
                                        SkipUntilEndOfScope(myfile, line);
                                    }
                                }
                            }
                        }
                        else
                        {
                            std::cout << "\nLine " << line << ": Error! Invalid condition! Use numbers or declared variables!\n";
                            return -1;
                        }
                    }
                    else
                    {
                        std::cout << "\nLine " << line << ": Error! Invalid condition! Check square brackets!\n";
                        return -1;
                    }
                }
                else
                {
                    std::cout << "\nLine " << line << ": Error! Invalid condition! Use \"M\", \"MH\", \"P\", \"PH\", \"H\" or \"AH\"!\n";
                    return -1;
                }
            }
            else
            {
                std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
                return -1;
            }

        }
        else
        {
            std::cout << "\nLine " << line << ": Error! Wrong statement!\n";
            return -1;
        }
        vecstr.clear();
        vecstr.shrink_to_fit();
    }
    vecint.clear();
    vecint.shrink_to_fit();
}