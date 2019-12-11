#include "IntCodes.h"
#include "BigIntCodes.h"
#include <iostream>

using namespace std;

int BigGetResult(int code, int first, int second, int third)
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

int BigOptCode(vector<int>& Program, int DefaultInput, bool &IsFinished, int &pos, int OptionalInput)
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
	int RelativeBase = 0;


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
			case 2: // relative mode
				p = Program.at(pos + rel) + RelativeBase;
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
			result = BigGetResult(code, first, second);
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
			pos = BigGetResult(code, first, second, third);
			break;

		case 6:
			first = Program.at(PositionFirstParameter);
			second = Program.at(PositionSecondParameter);
			third = pos + ParametersInCommand + 1;
			pos = BigGetResult(code, first, second, third);
			break;

		case 9:
			first = Program.at(PositionFirstParameter);
			RelativeBase += first;
			pos += ParametersInCommand + 1;

		default:
			break;
		}

		// write for modes which support writing
		if (!(code == 4 || code == 5 || code == 6 || code == 9))
			Program.at(WritePosition) = result;

		// return if output code is called
		if (code == 4) std::cout << Output << "\n";
	}
}