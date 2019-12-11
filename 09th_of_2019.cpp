#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "DayHeaders.h"
#include "BigIntCodes.h"
#include "IntCodes.h"


using namespace std;



void Day_09(ifstream& InputFile)
{
	vector< long long int> CodeList;

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


	int UserInput = 1; // provided by the puzzle
	cout << "User input is: " << UserInput << "...\nAnd this is Part 1 solution: \n";
	vector< long long int> Program = CodeList; // clean copy of the program
	Program.resize(1000000); // resize the program so it can go past its end
	vector<int> AllResults = {}; // clean placeholder for results (not necessary in day 5)
	int ContinueFrom = 0; // position to continue running the program from (zero for day 5)
	bool IsFinished = false; // indicator that the program has hit code 99
	long int Output = BigOptCode(Program, UserInput, IsFinished, ContinueFrom);

	//cout << "and the solution is: " << AllResults.back() << "!\n";


	// solution part 1: 3638931938
	// -656035358 not correct
	// solution part 2:

}
