#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "DayHeaders.h"

using namespace std;

void Day_16(ifstream& InputFile)
{
	int Digit;
	vector<int> Pattern;

	// read integers one by one
	// fill solutions into a vector
	vector<char> ListOfDigits{ istream_iterator<char>{InputFile},{} };
	for (auto Digit : ListOfDigits)
	{
		Pattern.push_back(Digit-'0');
	}

	vector<int> BasePattern = { 0, 1, 0, -1 };


	
	vector<int> ResultPerRun;
	for (int pass = 0; pass < Pattern.size(); pass++)
	{
		vector<int> CurrentPattern(Pattern.size() - pass);
		copy(Pattern.begin() + pass, Pattern.end(), CurrentPattern.begin());
		int sum = 0;
		int i = 0;
		for (auto Digit : CurrentPattern)
		{
			sum += Digit * BasePattern.at(i);
			i == 3 ? i = 0 : i++;
		}
		ResultPerRun.push_back(abs(sum % 10));
	}


}