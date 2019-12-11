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



void Day_11(ifstream& InputFile)
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

/* You'll need to build a new emergency hull painting robot.
The robot needs to be able to move around on the grid of square panels on the side of your ship,
detect the color of its current panel, and paint its current panel black or white.
(All of the panels are currently black.)

The Intcode program will serve as the brain of the robot.
The program uses input instructions to access the robot's camera:
	provide 0 if the robot is over a black panel or
	1 if the robot is over a white panel.

Then, the program will output two values:

First, it will output a value indicating the color to paint the panel the robot is over:
	0 means to paint the panel black, and
	1 means to paint the panel white.

Second, it will output a value indicating the direction the robot should turn:
	0 means it should turn left 90 degrees,
	and 1 means it should turn right 90 degrees.

After the robot turns, it should always move forward exactly one panel.
	The robot starts facing up.

The robot will continue running for a while like this and halt when it is finished drawing.
Do not restart the Intcode computer inside the robot during this process. */

	int UserInput = 1; // provided by the puzzle
	cout << "User input is: " << UserInput << "...\nAnd this is Part 1 solution: \n";
	vector< long long int> Program = CodeList; // clean copy of the program
	Program.resize(1000000); // resize the program so it can go past its end
	int ContinueFrom = 0; // position to continue running the program from (zero for day 5)
	bool IsFinished = false; // indicator that the program has hit code 99
	long int Output = BigOptCode(Program, UserInput, IsFinished, ContinueFrom);


	// solution part 1:
	// solution part 2:

}
