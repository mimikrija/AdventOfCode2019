#pragma once
#include <vector>

// INTCode stuff

 long long int BigGetResult(int code,  long long int first = 0,  long long int second = 0, long long int third = 0);
 long long int BigOptCode(std::vector< long long int>& Program,  long long int DefaultInput, bool &IsFinished, int &pos, long long int OptionalInput = -1);
