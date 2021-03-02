#include <iostream>
#include <fstream>
#include "Helpers.h"

void ProcessString(std::string& str);

int MoveToScope(std::ifstream& myfile, std::vector<KandV>& vecint, short& line);

void SkipUntilEndOfScope(std::ifstream& myfile, short& line);

int PureInterpret(std::string str, std::vector<KandV>& vecint, short& line);

std::vector<std::string> CreateLoopScope(std::ifstream& myfile);

int InterpretLoopScope(const std::vector<std::string>& vecline, std::vector<KandV>& vecint, short& line);

int InterpretC_relis(std::ifstream& myfile);