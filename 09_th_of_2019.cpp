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

void OptCode09(vector<long long int>& Program, int DefaultInput,  bool &IsFinished, int &pos,int OptionalInput = -1)
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
	long long int Output = 0;
	int RelativeBase = 0;
	
	//int pos = continuefrom;
	int code = 0;

	
	while ( code != 99)
	{
		long long int result;
		int code = GetCode(Program.at(pos));
		if (code == 99)
		{
			pos++; // useless now
			IsFinished = true;
			return;
		}

		int ParametersInCommand = NumberOfParameters(code);
		int PositionModeFirst = GetFirstParameterMode(Program.at(pos));
		int PositionModeSecond, PositionModeThird;
		long long int FirstParameter, SecondParameter, ThirdParameter;
		int WritePosition = 0;

		// default
		if (ParametersInCommand >= 1)
		{
			switch (PositionModeFirst)
			{
			case 0: // position mode
				FirstParameter = Program.at(Program.at(pos + 1));
				break;
			case 1: // immediate mode
				FirstParameter = Program.at(pos + 1);
				break;
			case 2: // relative mode
				FirstParameter = Program.at(Program.at(pos + 1) + RelativeBase);
				WritePosition = Program.at(pos + 1) + RelativeBase;
				cout << "code is: " << code << "\n";
				cout << "First parameter: " << FirstParameter << " ";
				break;
			default:
				break;
			}
		}
		if (ParametersInCommand >= 2)
		{
			PositionModeSecond = GetSecondParameterMode(Program.at(pos));
			switch (PositionModeSecond)
			{
			case 0: // position mode
				SecondParameter = Program.at(Program.at(pos + 2));
				break;
			case 1: // immediate mode
				SecondParameter = Program.at(pos + 2);
				break;
			case 2: // relative mode
				SecondParameter = Program.at(Program.at(pos + 2) + RelativeBase);
				cout << "Second parameter: " << SecondParameter << " ";
				break;
			default:
				break;
			}
		}
		if (ParametersInCommand >= 3)
		{
			PositionModeThird = GetThirdParameterMode(Program.at(pos));
			switch (PositionModeThird)
			{
			case 0: // position mode
				ThirdParameter = Program.at(pos + 3);
				break;
			case 1: // immediate mode
				ThirdParameter = pos + 3;
				break;
			case 2: // relative mode
				ThirdParameter = Program.at(pos + 3) + RelativeBase;
				cout << "Third(write) parameter " << ThirdParameter << "\n";
				break;
			default:
				break;
			}
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

		case 9:
			RelativeBase += FirstParameter;
			pos += ParametersInCommand + 1;
			break;
		default:
			break;
		}

		// exclude codes which do not write
		if (!(code == 4 || code == 5 || code == 6 || code == 9))
			Program.at(WritePosition) = result;

		if (code == 4) cout << "Current output: " << Output;

		// once we have output proceed to the next amplifier
	}
	
	
}



void Day_09(ifstream& InputFile)
{
	vector<long long int> Program;

	// read integers one by one
	// fill solutions into a vector
	string line;
	while (getline(InputFile, line))
	{
		stringstream linestream(line);
		string value;

		while (getline(linestream, value, ','))
		{
			Program.push_back(stoi(value));
		}
	}


	Program.resize(10000000);
	
	
	int Input = 1; // initial input;
	bool InitialRun = false;
	bool IsFinished = false;
	int ProgramPosition = 0;
	
	OptCode09(Program, Input, IsFinished, ProgramPosition);

	

}
