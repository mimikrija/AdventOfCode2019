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
}