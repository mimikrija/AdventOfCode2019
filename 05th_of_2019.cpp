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
	if (BigCode == 3) return 1;
	else return (BigCode / 100) % 10;
}

int GetSecondParameterMode(int BigCode)
{
	return (BigCode / 1000) % 10;
}

int GetThirdParameterMode(int BigCode)
{
	return (BigCode / 10000) % 10;
}

void Day_05(ifstream& InputFile)
{
	vector<int> CodeList, CleanCodeList;

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

	CleanCodeList = CodeList;


	int pos = 0;
	int InputValue = 1; //we provide that to the program
	while ( pos < CodeList.size())
	{
		int result;
		int code = GetCode(CodeList.at(pos));
		if (code == 99)
		{
			pos++;
			break;
		}
		// need to add switches because 3 and 4 don't take args the same way
		int firstarg;
		if (GetFirstParameterMode(CodeList.at(pos)) == 0)
		{
			// position mode
			firstarg = CodeList.at(CodeList.at(pos + 1));
		}
		else
		{
			// immediate mode
			firstarg = CodeList.at(pos + 1);
		}

		int secondarg;
		if (GetSecondParameterMode(CodeList.at(pos)) == 0)
		{
			// position mode
			secondarg = CodeList.at(CodeList.at(pos + 2));
		}
		else
		{
			// immediate mode
			secondarg = CodeList.at(pos + 2);
		}

		int inputpos = CodeList.at(pos + 3);

		switch (code)
		{
		case 1: // takes three arguments
			CodeList.at(inputpos) = firstarg + secondarg;
			pos += 4;
			break;
		case 2: // takes three arguments
			CodeList.at(inputpos) = firstarg * secondarg;
			pos += 4;
			break;
		case 3: // takes one argument
			CodeList.at(inputpos) = InputValue;
			pos += 2;
			break;
		case 4: // takes one argument
			cout << firstarg;
			pos += 2;
		default:
			break;
		}
	}

	cout << "Part one solution is: " << CodeList.at(0) << "!\n";

	// part 2

	
}
