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


	vector<int> UserInputs = { 1,5 };//we provide that to the program
	for (auto UserInput : UserInputs)
	{
		cout << "User input is: " << UserInput << "...";
		vector<int> Program = CodeList; // clean copy of the program
		vector<int> AllResults = {}; // clean placeholder for results (not necessary in day 5)
		int ContinueFrom = 0; // position to continue running the program from (zero for day 5)
		bool IsFinished = false; // indicator that the program has hit code 99
		while (!IsFinished)
		{
			int Output = OptCode(Program, UserInput, IsFinished, ContinueFrom);
			if (!IsFinished) AllResults.push_back(Output);
		}
		cout << "and the solution is: " << AllResults.back() << "!\n";
	}
	// solution part 1: 13346482
	// solution part 2: 12111395

}
