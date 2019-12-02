#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "DayHeaders.h"

using namespace std;

void Day_03(ifstream& InputFile)
{
	int ElfInput;
	vector<int> FuelEstimateList, FuelEstimateListForReal;

	// read integers one by one
	// fill solutions into a vector
	while (InputFile >> ElfInput)
	{
		FuelEstimateList.push_back(ElfInput);
	}

	vector<int> CodeList;

	// read comma separated data
	string line;
	while (getline(InputFile, line))
	{
		stringstream linestream(line);
		string value;

		while (getline(linestream, value, ','))
		{
			CodeList.push_back(stoi(value));
		}
	}
}
