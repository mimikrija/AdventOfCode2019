#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "DayHeaders.h"


using namespace std;

int GetCode(int BigCode)
{
	if (BigCode < 100) return BigCode;
	if (BigCode < 1000) return BigCode % 10;
	if (BigCode < 10'000) return BigCode % 100;
	return BigCode % 1'000;
}

int GetFirstParameterMode(int BigCode)
{
	//  always use immediate mode for code 3!
	if ( GetCode(BigCode) == 3 ) return 1;
	return (BigCode / 100) % 10;
}

int GetSecondParameterMode(int BigCode)
{
	return (BigCode / 1000) % 10;
}

int GetThirdParameterMode(int BigCode)
{
	//  always use immediate mode for codes 1, 2, 7, 8!
	if (GetCode(BigCode) == 1 || GetCode(BigCode) == 2
		|| GetCode(BigCode) == 7 || GetCode(BigCode) == 8) return 1;
	return (BigCode / 10000) % 10;
}

int NumberOfParameters(int code)
{
	switch (code)
	{
	case 1: case 2: case 7: case 8:
		return 3;

	case 3: case 4:
		return 1;

	case 5: case 6:
		return 2;
	}
}

int GetResult(int code, int first, int second)
{
	switch (code)
	{
	case 1:
		return first + second;
	case 2:
		return first*second;
	case 4:
		return first;
	case 7:
		if (first < second) return 1;
		else return 0;
	case 8:
		if (first == second) return 1;
		else return 0;
	default:
		return 0;
	}
}


void Day_05(ifstream& InputFile)
{
	vector<int> CodeList;

	// read integers one by one
	// fill solutions into a vector
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


	vector<int> UserInputs = { 1,5 };//we provide that to the program
	for (auto UserInput : UserInputs)
	{
		cout << "User input is: " << UserInput << "...";
		vector<int> Program = CodeList; // clean copy of the program
		vector<int> AllResults = {}; // clean placeholder for results (not necessary in day 5)
		int ContinueFrom = 0; // position to continue running the program from (zero for day 5)
		bool IsFinished = false; // indicator that the program has hit code 99
		while (!IsFinished)
		{
			int Output = OptCode(Program, UserInput, IsFinished, ContinueFrom);
			if (!IsFinished) AllResults.push_back(Output);
		}
		cout << "and the solution is: " << AllResults.back() << "!\n";
	}
	// solution part 1: 13346482
	// solution part 2: 12111395

}
