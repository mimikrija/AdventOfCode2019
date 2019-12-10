#include <iostream>
#include <fstream>
#include <string>
#include "DayHeaders.h"
#pragma once


using namespace std;


int main()
{
	// we can read that from the input file name
	cout << "Which day of Christmas? \n";
	int day;
	cin >> day;
	string leadingzero;
	day < 10 ? leadingzero = "0" : leadingzero = "";
	std::string InputFileName = "../inputs/input" + leadingzero + to_string(day);
	ifstream InputFile(InputFileName);




	switch(day)
	{
	case 1:
		Day_01(InputFile);
		break;
	case 2:
		Day_02(InputFile);
		break;
	case 3:
		Day_03(InputFile);
		break;
	case 4:
		Day_04(InputFile);
		break;
	case 5:
		Day_05(InputFile);
		break;
	case 6:
		Day_06(InputFile);
		break;
	case 7:
		Day_07(InputFile);
		break;
	case 8:
		Day_08(InputFile);
		break;
	case 9:
		Day_09(InputFile);
		break;
	}

	return 0;
}
