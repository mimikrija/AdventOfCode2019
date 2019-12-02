#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DayHeaders.h"


using namespace std;


void Day_02(ifstream& InputFile)
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

	CodeList.at(1) = 12;
	CodeList.at(2) = 2;
	
	for (int pos = 0; pos < CodeList.size(); pos++)
	{
		int result;
		int code = CodeList.at(pos*4);
		if (code == 99) break;
		int inputpos = CodeList.at(pos*4 + 3);
		int firstarg = CodeList.at(pos*4 + 1);
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
	
	cout << CodeList[0];
	// too low 530607
}
