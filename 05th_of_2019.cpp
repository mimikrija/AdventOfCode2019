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
	if (BigCode == 3) return 0;
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

int GetArgumentCount(int code)
{
	switch (code)
	{
	case 1:
		return 3;
	case 2:
		return 3;
	case 3:
		return 1;
	case 4:
		return 1;
	}
}

int GetResult(int code, int first = 0, int second = 0)
{
	switch (code)
	{
	case 1:
		return first + second;
	case 2:
		return first*second;
	case 3:
		return 0; // no output
	case 4:
		return first;
	default:
		return 0;
	}
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
	while ( pos <= CodeList.size())
	{
		int result;
		int code = GetCode(CodeList.at(pos));
		if (code == 99)
		{
			pos++;
			break;
		}
		
		int RelativeWritePosition = GetArgumentCount(code);
		
		int firstarg;
		int secondarg;
		int WritePosition = 0;
		if (RelativeWritePosition == 3)
		{
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
			WritePosition = CodeList.at(pos + RelativeWritePosition);
		}
		if (RelativeWritePosition == 1)
		{
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
		}
		if (code == 3) WritePosition = firstarg;
		if (code == 4) firstarg = CodeList.at(pos + 1);

		switch (code)
		{
		case 1: // takes three arguments
			CodeList.at(WritePosition) = firstarg + secondarg;
			break;
		case 2: // takes three arguments
			CodeList.at(WritePosition) = firstarg * secondarg;
			break;
		case 3: // takes one argument
			CodeList.at(WritePosition) = InputValue;
			break;
		case 4: // takes one argument
			cout << "Output produced " << CodeList.at(firstarg) << "\n";
		default:
			break;
		}
		pos += RelativeWritePosition + 1;
	}
// not 224224224224224224224224223 too high
// not 99
	// 223 too low
	//


	// part 2

	
}
