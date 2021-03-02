#include <string>
#include <vector>

#ifndef KANDV
#define KANDV

struct KandV
{
    std::string key;
    double value;
};

#endif

std::vector<short> FindCharIndexes(const std::string& str);

void FillVec(std::vector<std::string>& vec, const std::string& str);

bool IsDigitOrDot(char ch);

bool IsStrDoub(const std::string& str);

bool IsStrEmpty(const std::string& str);

bool IsValidOperator(const std::string& str);

bool IsValidCondition(const std::string& cond);

bool Cond(double num1, std::string cond, double num2);

double Calc(double num1, std::string oper, double num2);

int VectorIncludes(const std::vector<KandV>& vec, const std::string& str);

int VectorIncludes(const std::vector<std::string>& vec, const std::string& str);

bool IsPrintable(const std::vector<std::string>& vecstr, const std::vector<KandV>& vecint);