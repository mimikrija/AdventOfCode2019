#pragma once
#include <vector>

// INTCode stuff

int BigGetResult(int code, int first = 0, int second = 0, int third = 0);
int BigOptCode(std::vector<int>& Program, int DefaultInput, bool &IsFinished, int &pos, int OptionalInput = -1);
