#include <fstream>
#pragma once

void Day_01(std::ifstream& InputFile);
void Day_02(std::ifstream& InputFile);
void Day_03(std::ifstream& InputFile);
void Day_04(std::ifstream& InputFile);
void Day_05(std::ifstream& InputFile);
void Day_06(std::ifstream& InputFile);
void Day_07(std::ifstream& InputFile);
void Day_08(std::ifstream& InputFile);

// INTCOMstuff

int GetCode(int BigCode);
int GetFirstParameterMode(int BigCode);
int GetSecondParameterMode(int BigCode);
int GetThirdParameterMode(int BigCode);
int NumberOfParameters(int code);
int GetResult(int code, int first = 0, int second = 0);
