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

int GetCode(int BigCode)
{
	if (BigCode < 100) return BigCode;
	if (BigCode < 1000) return BigCode % 10;
	if (BigCode < 10'000) return BigCode % 100;
	return BigCode % 1'000;
}

int GetFirstParameterMode(int BigCode)
{
	return (BigCode / 100)%10;
}

int GetSecondParameterMode(int BigCode)
{
	return (BigCode / 1000) % 10;
}

int GetThirdParameterMode(int BigCode)
{
	return (BigCode / 10000) % 10;
}

void Day_05(ifstream& InputFile)
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

	int pos = 0;
	while ( pos < CodeList.size())
	{
		int result;
		int code = GetCode(CodeList.at(pos));
		if (code == 99)
		{
			pos++;
			break;
		}
		int firstarg;
		if (GetFirstParameterMode(CodeList.at(pos)) == 0)
		{
			// position mode
			firstarg = CodeList.at(CodeList.at(pos + 1));
		}
		else
		{
			// immediate mode
			firstarg = CodeList.at(pos + 1);
		}

		int secondarg;
		if (GetSecondParameterMode(CodeList.at(pos)) == 0)
		{
			// position mode
			secondarg = CodeList.at(CodeList.at(pos + 2));
		}
		else
		{
			// immediate mode
			secondarg = CodeList.at(pos + 2);
		}

		int inputpos = CodeList.at(pos + 3);

		switch (code)
		{
		case 1: // takes three arguments
			CodeList.at(inputpos) = firstarg + secondarg;
			pos += 4;
			break;
		case 2: // takes three arguments
			CodeList.at(inputpos) = firstarg * secondarg;
			pos += 4;
			break;
		case 3: // takes one argument
			CodeList.at(inputpos) = firstarg;
			pos += 2;
			break;
		case 4: // takes one argument
			cout << CodeList.at(firstarg);
			pos += 2;
		default:
			break;
		}
	}

	cout << "Part one solution is: " << CodeList.at(0) << "!\n";

	// part 2

	int noun, verb;
	int nounsize = CleanCodeList.size();
	vector<int> Nouns(nounsize);
	iota(Nouns.begin(), Nouns.end(), 0);
	vector<int> Verbs;
	Verbs = Nouns;
	vector<pair<int, int>> Combinations;
	pair<int, int> OneCombination;
	for_each(Nouns.begin(), Nouns.end(),
		[Verbs, &OneCombination, &Combinations](int ANoun)
	{
		for_each(Verbs.begin(), Verbs.end(),
			[ANoun,&OneCombination,&Combinations](int AVerb)
		{OneCombination = make_pair(ANoun, AVerb);
		Combinations.push_back(OneCombination); }
		);
		
	});

	for (auto NounAndVerb : Combinations)
	{
		CodeList = CleanCodeList;
		noun = NounAndVerb.first;
		verb = NounAndVerb.second;
		CodeList.at(1) = noun;
		CodeList.at(2) = verb;
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
		if (CodeList.at(0) == 19690720) break;
	}

	cout << "Part two solution is: " << 100 * noun + verb << "!\n";

}
