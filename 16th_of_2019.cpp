#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>
#include "DayHeaders.h"

using namespace std;

vector<vector<int>> PatternPerPass (vector<int> Input)
{
	vector<int> BasePattern = { 0, 1, 0, -1 };
	vector<vector<int>> BasePatterns(Input.size());
	int pass = 1;
	for (auto &PaternPerPass : BasePatterns)
	{
		int i = 0;
		for (auto counter = 1; counter <= Input.size() + 1; counter++)
		{
			PaternPerPass.push_back(BasePattern.at(i));
			if (counter % pass == 0)
			{
				i == 3 ? i = 0 : i++;
			}
		}
		rotate(PaternPerPass.begin(), PaternPerPass.begin() + 1, PaternPerPass.end());
		PaternPerPass.resize(Input.size());
		pass++;
	}
	return BasePatterns;
}

void GetSolution(vector<int> Input, vector<vector<int>> BasePatterns, int MessageOffset)
{
	vector<int> Result = Input;
	vector<int> BasePattern = { 0, 1, 0, -1 };
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
			if (phase == 100 && run > MessageOffset && run <= MessageOffset + 8) cout << abs(sum % 10);
		}
	}
}

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
	



	
	// get phase patterns
	vector<vector<int>> BasePatterns = PatternPerPass(Pattern);

	
	cout << "Part 1 solution is: ";
	GetSolution(Pattern, BasePatterns, 0);
	cout << "\n";

	// part 2
	vector<int> PatternPartTwo;
	for (int count = 1; count <= 10'000; count++) PatternPartTwo.insert(PatternPartTwo.end(), Pattern.begin(), Pattern.end());
	int count = -1;
	//auto MessageOffset = accumulate(Pattern.begin(), Pattern.begin() + 6, 0, [](auto &digit) { return digit*2 ; });
	long int MessageOffset = 0;
	for_each(Pattern.begin(), Pattern.begin() + 7, [&count,&MessageOffset](int digit) {count++; MessageOffset+= int(digit * pow(10, count)); });

	cout << "Part 2 solution is: ";
	vector<vector<int>> BasePatternsPartTwo = PatternPerPass(PatternPartTwo);
	GetSolution(PatternPartTwo, BasePatternsPartTwo, MessageOffset);
	cout << "\n";

	// part 1: 58672132

}