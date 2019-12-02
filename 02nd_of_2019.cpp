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

	CleanCodeList = CodeList;
	CodeList.at(1) = 12;
	CodeList.at(2) = 2;


	for (int pos = 0; pos < CodeList.size(); pos++)
	{
		int result;
		int code = CodeList.at(pos * 4);
		if (code == 99) break;
		int inputpos = CodeList.at(pos * 4 + 3);
		int firstarg = CodeList.at(pos * 4 + 1);
		int secondarg = CodeList.at(pos * 4 + 2);
		switch (code)
		{
		case 1:
			CodeList.at(inputpos) = CodeList.at(firstarg) + CodeList.at(secondarg);
			break;
		case 2:
			CodeList.at(inputpos) = CodeList.at(firstarg) * CodeList.at(secondarg);
			break;
		default:
			break;
		}

	}

	cout << CodeList[0] << "\n";

	// part 2

	int noun = 2;
	int verb = 13;
	bool change = true;
	vector<int> Nouns(CleanCodeList.size() - 1), Verbs(CleanCodeList.size() - 1);;
	iota(Nouns.begin(), Nouns.end(), 0);
	iota(Verbs.begin(), Verbs.end(), 0);

	while (CodeList.at(0) != 19690720)
	{
		CodeList = CleanCodeList;
		CodeList.at(1) = Nouns.back();
		CodeList.at(2) = Verbs.back();
		for (int pos = 0; pos < CodeList.size(); pos++)
		{
			int result;
			int code = CodeList.at(pos * 4);
			if (code == 99) break;
			int inputpos = CodeList.at(pos * 4 + 3);
			int firstarg = CodeList.at(pos * 4 + 1);
			int secondarg = CodeList.at(pos * 4 + 2);
			switch (code)
			{
			case 1:
				CodeList.at(inputpos) = CodeList.at(firstarg) + CodeList.at(secondarg);
				break;
			case 2:
				CodeList.at(inputpos) = CodeList.at(firstarg) * CodeList.at(secondarg);
				break;
			default:
				break;
			}
		}
		if (change)
		{
			Nouns.resize(Nouns.size() - 1);
			change = false;
		}
		else
		{
			Verbs.resize(Verbs.size() - 1);
			change = true;
		}
		
	}
		
	

	//while (CodeList[0] != 19690720)
	cout << 100 * noun + verb;
}
