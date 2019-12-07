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

void Day_07(ifstream& InputFile)
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
		bool PositionModeSecond, PositionModeThird;
		int FirstParameter, SecondParameter, ThirdParameter;
		int WritePosition = 0;
		
		// default
		if (ParametersInCommand >= 1)
		{
			PositionModeFirst ?
				FirstParameter = CodeList.at(CodeList.at(pos + 1))
				:
				FirstParameter = CodeList.at(pos + 1);
		}
		if (ParametersInCommand >= 2)
		{
			PositionModeSecond = !GetSecondParameterMode(CodeList.at(pos));
			PositionModeSecond ?
				SecondParameter = CodeList.at(CodeList.at(pos + 2))
				:
				SecondParameter = CodeList.at(pos + 2);
		}
		if (ParametersInCommand >= 3)
		{
			PositionModeThird = !GetThirdParameterMode(CodeList.at(pos));
			PositionModeThird ?
				ThirdParameter = CodeList.at(CodeList.at(pos + 3))
				:
				ThirdParameter = CodeList.at(pos + 3);
		}


		switch (code)
		{
		case 1: case 2: case 7: case 8:
			result = GetResult(code, FirstParameter, SecondParameter);
			WritePosition = ThirdParameter;
			pos += ParametersInCommand + 1;
			break;

		case 3:
			WritePosition = FirstParameter;
			result = UserInput;
			pos += ParametersInCommand + 1;
			break;

		case 4:
			result = FirstParameter;
			cout << "Output produced " << result << "\n";
			pos += ParametersInCommand + 1;
			break;

		case 5:
			FirstParameter != 0 ? pos = SecondParameter : pos+= ParametersInCommand + 1;
			break;

		case 6:
			FirstParameter == 0 ? pos = SecondParameter : pos += ParametersInCommand + 1;
			break;

		default:
			break;
		}

		// exclude codes which do not write
		if ( !( code == 4 || code ==5 || code ==6))
			CodeList.at(WritePosition) = result;
		
	}


}
