#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include "DayHeaders.h"
#pragma once

using namespace std;

void Day_01(ifstream& InputFile)
{
	int ElfInput;
	vector<int> FuelInstructionList;

	// read integers one by one into a vector
	while (InputFile >> ElfInput)
	{
		FuelInstructionList.push_back(ElfInput);
	}
}