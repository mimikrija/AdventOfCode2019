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
	vector<int> AmplifierInputs = {0, 1, 2, 3, 4};
	while (next_permutation(AmplifierInputs.begin(), AmplifierInputs.end()))
	{
		vector<int> AmplifierResults(5,0);
		vector<vector<int>> AmplifierPrograms{ 5,CodeList };
		vector<int> ContinueFrom(5, 0);
		bool InitialRun = true;
		bool IsFinished = false;
		int i = 0;
		int Input = 0; // this is the initial input for A
		int Output;
		for (i = 0; i < 5; i ++)
		{
			InitialRun = true;
			Output = OptCode(AmplifierPrograms.at(i), Input, IsFinished, ContinueFrom.at(i), AmplifierInputs.at(i));
			Input = Output;
			AmplifierResults.at(i)= Output;
		}
		AllResults.push_back(AmplifierResults.at(4));

	}

	cout << "Part 1 solution is " << *max_element(AllResults.begin(), AllResults.end()) << "!\n";

	


	// part 2
	AmplifierInputs = { 5,6,7,8,9 };
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
