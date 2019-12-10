#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "DayHeaders.h"
#include "IntCodes.h"


using namespace std;


void Day_02(ifstream& InputFile)
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
	
	// part 1: initialize the program with values from the puzzle
	vector<int> Program = CodeList; // clean copy of the program
	Program.at(1) = 12;
	Program.at(2) = 2;
	int UserInput = 0; // not necessary in day 2
	int ContinueFrom = 0; // position to continue running the program from (zero for day 5)
	bool IsFinished = false; // indicator that the program has hit code 99
	
	while (!IsFinished)
	{
		int Output = OptCode(Program, UserInput, IsFinished, ContinueFrom);
	}
	cout << "Part one solution is: " << Program.at(0) << "!\n";

	// part 2: test various noun-verb combinations
	int noun, verb;
	for (noun = 99; noun >= 0; noun--)
	{
		for (verb = 99; verb >= 0; verb--)
		{
			Program = CodeList; // clean copy of the program
			Program.at(1) = noun;
			Program.at(2) = verb;
			int UserInput = 0; // not necessary in day 2
			int ContinueFrom = 0; // position to continue running the program from
			bool IsFinished = false; // indicator that the program has hit code 99

			while (!IsFinished)
			{
				int Output = OptCode(Program, UserInput, IsFinished, ContinueFrom);
			}
			if (Program.at(0) == 19690720) break; // very elegant way of breaking out
		}
		if (Program.at(0) == 19690720) break; //	 of a quadratic loop.
	}
	
	cout << "Part two solution is: " << 100 * noun + verb << "!\n";
	
	// Part one solution is : 3516593!
	// Part two solution is : 7749!
}
