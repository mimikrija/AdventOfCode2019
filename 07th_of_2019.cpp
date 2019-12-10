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

int OptCode(vector<int>& Program, int DefaultInput,  bool &IsFinished, int &pos,int OptionalInput = -1)
{
	// Program is taken by reference because it is changed and needs to remain that way
	// even after this runs

	// Default Input is (in this case) the output of the previous amplifier, but it can
	// be used for any default input

	// OptionalInput is used only when provided - in this case only in the initial run
	// when we provide the phase code to each amplifier.
	// in this case, the phase codes are 0-9 - so -1 is a safe choice for 
	// checking whether to use this input or not

	// IsFinished, also by reference serves to communicate to the main program whether that
	// amplifier is finished or not (hit code 99)
	int Output = 0;
	
	bool PhaseInput = true;
	//int pos = continuefrom;

	
	while (pos < Program.size())
	{
		int result;
		int code = GetCode(Program.at(pos));
		if (code == 99)
		{
			pos++; // useless now
			IsFinished = true;
			return Output; //not that it matters?
		}

		int ParametersInCommand = NumberOfParameters(code);
		bool PositionModeFirst = !GetFirstParameterMode(Program.at(pos));
		bool PositionModeSecond, PositionModeThird;
		int FirstParameter, SecondParameter, ThirdParameter;
		int WritePosition = 0;

		// default
		if (ParametersInCommand >= 1)
		{
			PositionModeFirst ?
				FirstParameter = Program.at(Program.at(pos + 1))
				:
				FirstParameter = Program.at(pos + 1);
		}
		if (ParametersInCommand >= 2)
		{
			PositionModeSecond = !GetSecondParameterMode(Program.at(pos));
			PositionModeSecond ?
				SecondParameter = Program.at(Program.at(pos + 2))
				:
				SecondParameter = Program.at(pos + 2);
		}
		if (ParametersInCommand >= 3)
		{
			PositionModeThird = !GetThirdParameterMode(Program.at(pos));
			PositionModeThird ?
				ThirdParameter = Program.at(Program.at(pos + 3))
				:
				ThirdParameter = Program.at(pos + 3);
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
			OptionalInput >= 0 ? result = OptionalInput : result = DefaultInput;
			if (PhaseInput) PhaseInput = false;
			else result = DefaultInput;
			pos += ParametersInCommand + 1;
			break;

		case 4:
			result = FirstParameter;
			//cout << "Output produced " << result << "\n";
			pos += ParametersInCommand + 1;
			Output = result;
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
			Program.at(WritePosition) = result;

		if (code == 4) return Output;

		// once we have output proceed to the next amplifier
	}
	
	
}



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
	vector<int> AmplifierInputs = { 5,6,7,8,9 };


	// part 2
	CodeList = CleanCode;
	while (next_permutation(AmplifierInputs.begin(), AmplifierInputs.end()))
	{
		vector<vector<int>> AmplifierOutputs(5);
		vector<vector<int>> AmplifierPrograms{ 5,CodeList };
		vector<int> ContinueFrom(5);

		bool InitialRun = true;
		bool IsFinished = false;
		int i = 0;
		int Input = 0; // this is the initial input for A
		int Output;
		while (true)
		{
			if (i == 0 && InitialRun) Input = 0;
			else
			{
				i != 0 ? Input = (AmplifierOutputs.at(i - 1)).back() : Input = (AmplifierOutputs.at(4)).back();
			}
			if (InitialRun) // call with extra parameter as input
			{
				Output = OptCode(AmplifierPrograms.at(i), Input, IsFinished, ContinueFrom.at(i), AmplifierInputs.at(i));
				if (i == 4) InitialRun = false;
			}
			else // call with default parameters
			{
				Output = OptCode(AmplifierPrograms.at(i), Input, IsFinished, ContinueFrom.at(i));
			}
			if (!IsFinished) AmplifierOutputs.at(i).push_back(Output);
			if (i != 4) IsFinished = false;
			if (IsFinished) break;

			i == 4 ? i = 0 : i++;
		}
		AllResults.push_back(*max_element(AmplifierOutputs.at(4).begin(), AmplifierOutputs.at(4).end()));


		
	}
	cout << "Part 2 solution is " << *max_element(AllResults.begin(), AllResults.end()) << "!\n";
	// Part 1: 65464
	// Part 2: 1518124
}
