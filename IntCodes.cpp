#include "IntCodes.h"

using namespace std;

int GetCode(int BigCode)
{
	if (BigCode < 100) return BigCode;
	if (BigCode < 1000) return BigCode % 10;
	if (BigCode < 10'000) return BigCode % 100;
	return BigCode % 1'000;
}

vector<int> CodesAndModes(int BigCode)
{
	// code and modes would be more precise
	// but this rhymes.
	vector<int> CodesAndModes(4,0);
	// 0-th entry is the code
	CodesAndModes.at(0) = GetCode(BigCode);
	// 1-th entry is the first parameter.. etc.
	CodesAndModes.at(1) = (BigCode / 100) % 10;
	CodesAndModes.at(2) = (BigCode / 1000) % 10;
	CodesAndModes.at(3) = (BigCode / 10000) % 10;
	// yes, this could have been a loop but it is
	// actually more clear like this!

	return CodesAndModes;
}

int GetFirstParameterMode(int BigCode)
{
	//  always use immediate mode for code 3!
	if (GetCode(BigCode) == 3) return 1;
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

int GetResult(int code, int first, int second, int third)
{
	switch (code)
	{
	case 1:
		return first + second;
	case 2:
		return first*second;
	case 4:
		return first;
	case 5: //			FirstParameter != 0 ? pos = SecondParameter : pos += ParametersInCommand + 1;
		if (first != 0) return second;
		else return third;
		break;
	case 6:			//FirstParameter == 0 ? pos = SecondParameter : pos += ParametersInCommand + 1;
		if (first == 0) return second;
		else return third;
		break;
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

int OptCode(vector<int>& Program, int DefaultInput, bool &IsFinished, int &pos, int OptionalInput)
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
		vector<int> CodeAndMode = CodesAndModes(Program.at(pos));
		int code = CodeAndMode.at(0);
		
		if (code == 99)
		{
			pos++; // useless now
			IsFinished = true;
			return 0; //not that it matters?
					  // ugh I have to return something from this function, but I take care that
					  // the last (this) output is ignored when calling this function.
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
			first = Program.at(PositionFirstParameter);
			second = Program.at(PositionSecondParameter);
			result = GetResult(code, first, second);
			WritePosition = PositionThirdParameter;
			pos += ParametersInCommand + 1;
			break;

		case 3:
			WritePosition = PositionFirstParameter;
			OptionalInput >= 0 ? result = OptionalInput : result = DefaultInput;
			if (PhaseInput) PhaseInput = false;
			else result = DefaultInput;
			pos += ParametersInCommand + 1;
			break;

		case 4:
			result = Program.at(PositionFirstParameter);
			//cout << "Output produced " << result << "\n";
			pos += ParametersInCommand + 1;
			Output = result;
			break;

		case 5:
			first = Program.at(PositionFirstParameter);
			second = Program.at(PositionSecondParameter);
			third = pos + ParametersInCommand + 1;
			pos = GetResult(code, first, second, third);
			//FirstParameter != 0 ? pos = SecondParameter : pos += ParametersInCommand + 1;
			break;

		case 6:
			first = Program.at(PositionFirstParameter);
			second = Program.at(PositionSecondParameter);
			third = pos + ParametersInCommand + 1;
			pos = GetResult(code, first, second, third);
			//FirstParameter == 0 ? pos = SecondParameter : pos += ParametersInCommand + 1;
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