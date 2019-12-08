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
	
	vector<int> CleanCode = CodeList;
	vector<int> AllResults;
	vector<int> AmplifierInputs = { 0,1,2,3,4 };

	while (next_permutation(AmplifierInputs.begin(),AmplifierInputs.end()))
	{

		int LastOutput = 0;
		for (int i = 0; i < 5; i++)
		{
			int inputcount = 0;

			int UserInput = AmplifierInputs.at(i);//we provide that to the program
			//cin >> UserInput;
			//cout << "Amplifier number " << i << " running. Phase setting: " << UserInput << "\n";
			int pos = 0;

			CodeList = CleanCode;
			while (pos < CodeList.size())
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
					if (inputcount == 0)
					{
						result = UserInput;
						inputcount++;
					}
					else result = LastOutput;
					pos += ParametersInCommand + 1;
					break;

				case 4:
					result = FirstParameter;
					//cout << "Output produced " << result << "\n";
					pos += ParametersInCommand + 1;
					LastOutput = result;
					break;

				case 5:
					FirstParameter != 0 ? pos = SecondParameter : pos += ParametersInCommand + 1;
					break;

				case 6:
					FirstParameter == 0 ? pos = SecondParameter : pos += ParametersInCommand + 1;
					break;

				default:
					break;
				}

				// exclude codes which do not write
				if (!(code == 4 || code == 5 || code == 6))
					CodeList.at(WritePosition) = result;

			}
		}
		AllResults.push_back(LastOutput);
	}

	cout << "Part 1 solution is " << *max_element(AllResults.begin(), AllResults.end()) << "!\n";


	AmplifierInputs = { 5,6,7,8,9 };
	vector < vector<int>> AmplifierPrograms;
	AmplifierPrograms = {};
	AllResults = {};
	bool IsAmplifierDone = false;

	for (auto i : AmplifierInputs) AmplifierPrograms.push_back(CleanCode);

	while (next_permutation(AmplifierInputs.begin(), AmplifierInputs.end()))
	{
		int inputcount = 0;
		int LastOutput;
		for (int i = 0; i < 5; i++)
		{

			int result;
			int UserInput;//we provide that to the program
			if (inputcount == 0)
			{
				UserInput = AmplifierInputs.at(i);
				inputcount++;
			}
			else UserInput = LastOutput;
			//cin >> UserInput;
			//cout << "Amplifier number " << i << " running. Phase setting: " << UserInput << "\n";
			int pos = 0;

			CodeList = AmplifierPrograms.at(i);
			while (pos < CodeList.size())
			{
				int result;
				int code = GetCode(CodeList.at(pos));
				if (code == 99)
				{
					pos++;
					break;//this amplifier is done!
					IsAmplifierDone = true;

				}
				else IsAmplifierDone = false;
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
					//cout << "Output produced " << result << "\n";
					pos += ParametersInCommand + 1;
					LastOutput = result;
					break;

				case 5:
					FirstParameter != 0 ? pos = SecondParameter : pos += ParametersInCommand + 1;
					break;

				case 6:
					FirstParameter == 0 ? pos = SecondParameter : pos += ParametersInCommand + 1;
					break;

				default:
					break;
				}

				// exclude codes which do not write
				if (!(code == 4 || code == 5 || code == 6))
					CodeList.at(WritePosition) = result;

			}
			//if (i == 4 && code)
			//if (!IsAmplifierDone && i == 4) i = 0;
			AmplifierPrograms.at(i) = CodeList;
		}
		
		AllResults.push_back(LastOutput);
	}

	cout << "Part 2 solution is " << *max_element(AllResults.begin(), AllResults.end()) << "!\n";


	// Part 1: 65464
}
