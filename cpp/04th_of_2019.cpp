#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DayHeaders.h"

using namespace std;

void Day_04(ifstream& InputFile)
{
	//read input (stream of chars is read into a string)
	string RangeOfPasswords{ istream_iterator<char>{InputFile},{} };
	
	// parse input
	int pos = RangeOfPasswords.find("-");
	int PassRangeBegin = stoi(RangeOfPasswords.substr(0,pos));
	int PassRangeEnd = stoi(RangeOfPasswords.substr(pos+1));

	int Counter = 0; // solution to part 1
	int CounterExtraRule = 0; // solution to part 2

	// convert strings to containers of integers
	for ( auto Candidate = PassRangeBegin; Candidate <= PassRangeEnd; Candidate++ )
	{
		string StringVersion = to_string(Candidate);
		vector<int> VectorCandidate = {};
		for (auto digit : StringVersion) VectorCandidate.push_back(digit-48);
		// rule 1: the digits must be in ascending order
		// rule 2: the password must contain at least two adjacent same digits
		if (!prev_permutation(VectorCandidate.begin(), VectorCandidate.end())
			&&
			adjacent_find(VectorCandidate.begin(), VectorCandidate.end()) != VectorCandidate.end())
		{
			Counter++;
			// part 2: extra rule:
			// there must be at least one repeating PAIR (no more than two)
			vector<int> UniqueDigits = VectorCandidate;
			auto it = unique(UniqueDigits.begin(), UniqueDigits.end());
			UniqueDigits.resize(it - UniqueDigits.begin());

			for (auto UniqueDigit : UniqueDigits)
			{
				if (count_if(VectorCandidate.begin(), VectorCandidate.end(),
					[UniqueDigit](int CandidateDigit)
				{return CandidateDigit == UniqueDigit; }) == 2)

				{
					CounterExtraRule++;
					break;
				}
			}
		}
	}

	cout << "The number of passwords satisfying the initial rule (part 1) is: " << Counter << "...\n";
	cout << "...of which " << CounterExtraRule << " satisty the extra rule!\n";

}
