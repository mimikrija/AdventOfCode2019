#include "IntCodes.h"

using namespace std;

int GetCode(int BigCode)
{
	if (BigCode < 100) return BigCode;
	else return BigCode % 10;
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

int NumberOfParameters(int code)
{
	switch (code)
	{
	case 1: case 2: case 7: case 8:
		return 3;

	case 3: case 4: case 9:
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

	// Default Input depends on the day:

	// day 02 - no input modes present, Input is a dummy
	// day 05 - only one input per run, Input is defined in 05th_of_2019.cpp
	// day 07 - two possible inputs: Input is the one that is always taken (from
	//			previous amplifier). OptionalInput is the phase setting of the amplifier.
	//			OptionalInput goes together with InitialRun boolean which governs whether
	//			to use it or not.
	bool PhaseInput = true; // this makes sense only if OptionalInput is present (day 07)

	// IsFinished, taken by reference  as it serves to communicate to the main program
	// whether that program is finished or not (hit code 99)
	
	// pos	position in the program. In days 02 and 05 not used, so we provide 0,
	//		otherwise this is provided as reference so that we can continue where we left
	//		off last time a program was run (day 07)

	int Output = 0;


	while (pos < Program.size())
	{
		int result;
		vector<int> CodeAndMode = CodesAndModes(Program.at(pos));
		int code = CodeAndMode.at(0);
		
		if (code == 99)
		{
			pos++; // useless, but for the sake of completeness.
			IsFinished = true;
			return 0;	//not that it matters?
						// ugh I have to return something from this function, but I take care that
						// the last (this) output is ignored when calling this function.
		}

		int ParametersInCommand = NumberOfParameters(code);

		// get parameter indices
		vector<int> ParameterIndices(ParametersInCommand);
		auto it = CodeAndMode.begin() + 1;
		for (auto& p : ParameterIndices)
		{
			int mode = *it;
			int rel = it - CodeAndMode.begin();
			it++;
			switch (mode)
			{
			case 0: // position mode
				p = Program.at(pos + rel);
				break;
			case 1: // imediate mode
				p = pos + rel;
				break;
			//case 2: // relative mode
				//p =
			default:
				break;
			}
		}
		int PositionFirstParameter, PositionSecondParameter, PositionThirdParameter;
		if (ParametersInCommand >= 1) PositionFirstParameter = ParameterIndices.at(0);
		if (ParametersInCommand >= 2) PositionSecondParameter = ParameterIndices.at(1);
		if (ParametersInCommand >= 3) PositionThirdParameter = ParameterIndices.at(2);
		int first, second, third, WritePosition;

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
			pos += ParametersInCommand + 1;
			Output = result;
			break;

		case 5:
			first = Program.at(PositionFirstParameter);
			second = Program.at(PositionSecondParameter);
			third = pos + ParametersInCommand + 1;
			pos = GetResult(code, first, second, third);
			break;

		case 6:
			first = Program.at(PositionFirstParameter);
			second = Program.at(PositionSecondParameter);
			third = pos + ParametersInCommand + 1;
			pos = GetResult(code, first, second, third);
			break;

		default:
			break;
		}

		// write for modes which support writing
		if (!(code == 4 || code == 5 || code == 6))
			Program.at(WritePosition) = result;

		// return if output code is called
		if (code == 4) return Output;
	}
}