#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
#include "DayHeaders.h"
#pragma once

using namespace std;

int FuelCalculation(int Input, bool part2 = false)
{
	int calculation = Input / 3 - 2;
	if (!part2) return calculation;
	else return(calculation > 0 ? calculation + FuelCalculation(calculation,true):0);
}

void Day_01(ifstream& InputFile)
{
	int ElfInput;
	vector<int> FuelEstimateList,FuelEstimateListForReal;

	// read integers one by one
	// fill solutions into a vector
	while (InputFile >> ElfInput)
	{
		FuelEstimateList.push_back(FuelCalculation(ElfInput));
		FuelEstimateListForReal.push_back(FuelCalculation(ElfInput,true));
	}

	int TotalFuelNeeded =
		accumulate(FuelEstimateList.begin(), FuelEstimateList.end(),0);

	int TotalFuelNeededForReal =
		accumulate(FuelEstimateListForReal.begin(), FuelEstimateListForReal.end(), 0);

	cout << "Total amount of fuel needed is: " << TotalFuelNeeded << "\n";
	cout << "LOL JK, total amount needed is actually: " << TotalFuelNeededForReal << "\n";

}

