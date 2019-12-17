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
	vector<vector<int>> BasePatterns(Pattern.size());
	
	// get phase patterns
	int pass = 1;
	for (auto &PaternPerPass : BasePatterns)
	{
		int i = 0;
		for (auto counter = 1; counter <= Pattern.size()+1; counter++)
		{
			PaternPerPass.push_back(BasePattern.at(i));
			if (counter % pass == 0)
			{
				i == 3 ? i = 0 : i++;
			}
		}
		rotate(PaternPerPass.begin(), PaternPerPass.begin() + 1, PaternPerPass.end());
		PaternPerPass.resize(Pattern.size());
		pass++;
	}

	// calculate 100 phases
	cout << "Part 1 solution is: ";
	vector<int> Result = Pattern;
	for (int phase = 1; phase <= 100; phase++)
	{
		int passcounter = 0;
		vector<int> CurrentPattern = Result;
		Result = {};
		//cout << "After phase " << phase << ": ";
		for (int run = 1; run <= CurrentPattern.size(); run++)
		{
			int sum = 0;

			int i = 0;
			for (auto Digit : CurrentPattern)
			{
				sum += Digit * (BasePatterns.at(passcounter)).at(i);
				i++;
			}
			passcounter++;
			Result.push_back(abs(sum % 10));
			if ( phase == 100 && run <= 8 ) cout << abs(sum % 10);
		}
	}
	cout << "\n";
	// part 1: 58672132

}