#pragma once
#include <vector>

// INTCode stuff

int GetCode(int BigCode);
int GetFirstParameterMode(int BigCode);
int GetSecondParameterMode(int BigCode);
int GetThirdParameterMode(int BigCode);
int NumberOfParameters(int code);
int GetResult(int code, int first = 0, int second = 0);
int OptCode(std::vector<int>& Program, int DefaultInput, bool &IsFinished, int &pos, int OptionalInput = -1);
