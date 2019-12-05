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
	return (BigCode / 10000) % 10;
}

int NumberOfParameters(int code)
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


	int pos = 0;
	cout << "Give me the input: ";
	int UserInput;//we provide that to the program
	cin >> UserInput;
	while ( pos < CodeList.size())
	{
		int result;
		int code = GetCode(CodeList.at(pos));
		if (code == 99)
		{
			pos++;
			break;
		}

		int ParametersInCommand = NumberOfParameters(code);
		bool PositionModeFirst = !GetFirstParameterMode(CodeList.at(pos));
		bool PositionModeSecond;
		int FirstParameter, SecondParameter;
		int WritePosition = 0;
		PositionModeFirst ?
			FirstParameter = CodeList.at(CodeList.at(pos + 1))
			:
			FirstParameter = CodeList.at(pos + 1);
		if (ParametersInCommand > 1)
		{
			PositionModeSecond = !GetSecondParameterMode(CodeList.at(pos));
			PositionModeSecond ?
				SecondParameter = CodeList.at(CodeList.at(pos + 2))
				:
				SecondParameter = CodeList.at(pos + 2);
		}

		switch (code)
		{
		case 1: case 2:
			result = GetResult(code, FirstParameter, SecondParameter);
			WritePosition = CodeList.at(pos + ParametersInCommand);
			break;

		case 3:
			WritePosition = FirstParameter;
			result = UserInput;
			break;

		case 4:
			result = FirstParameter;
			cout << "Output produced " << result << "\n";
			break;

		default:
			break;
		}

		// default writing behavior:
		if ( code != 4) CodeList.at(WritePosition) = result;
		pos += ParametersInCommand + 1;
	}

	// solution part 1: 13346482


	// part 2

}
