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
	// read input line per line
	//vector<string> ListOfInputs{ istream_iterator<string>{InputFile},{} };

	int PassRangeBegin = 136818;
	int PassRangeEnd = 685979;

	vector<int> FirstPassword;
	string CheckPassword = to_string(PassRangeBegin);

	// convert strings to containers of integers
	int Counter = 0;
	for (auto Candidate = PassRangeBegin; Candidate <= PassRangeEnd; Candidate++)
	{
		string StringVersion = to_string(Candidate);
		vector<int> VectorCandidate = {};
		for (auto digit : StringVersion) VectorCandidate.push_back(digit-48);
		if (!prev_permutation(VectorCandidate.begin(), VectorCandidate.end())
			&&
		adjacent_find(VectorCandidate.begin(),VectorCandidate.end()) != VectorCandidate.end())
			 Counter++;

	}

	cout << Counter;


}
