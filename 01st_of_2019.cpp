#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include "DayHeaders.h"
#pragma once

using namespace std;

int FuelCalculation(int Input)
{
	int calculation = int(Input / 3) - 2;
	if (calculation >= 0) return calculation;
	else return 0;
}

void Day_01(ifstream& InputFile)
{
	int ElfInput;
	vector<int> FuelInstructionList;

	// read integers one by one into a vector
	while (InputFile >> ElfInput)
	{
		FuelInstructionList.push_back(ElfInput);
	}

	int TotalFuelNeeded = 0;
	int maja = int(14 / 3);

	for_each(FuelInstructionList.begin(), FuelInstructionList.end(),
		[&TotalFuelNeeded](int ElfInput)
		{TotalFuelNeeded += FuelCalculation(ElfInput); });

	cout << "Total amount of fuel needed is: " << TotalFuelNeeded << "\n";

	int TotalFuelNeededForReal = 0;
	for_each(FuelInstructionList.begin(), FuelInstructionList.end(),
		[&TotalFuelNeededForReal](int ElfInput)
		{
			int tempinput = FuelCalculation(ElfInput);
			while (tempinput > 0)
			{
				TotalFuelNeededForReal += tempinput;
				tempinput = FuelCalculation(tempinput);
			}
		});

	cout << "LOL JK, total amount neede is actually: " << TotalFuelNeededForReal << "\n";
}