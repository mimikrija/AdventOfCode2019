#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <map>
#include <numeric>
#include "DayHeaders.h"

using namespace std;


void Day_06(ifstream& InputFile)
{
	map <string, string> OrbitDefintions;
	map <string, int> OrbitCounts;
	// parse input
	vector<string> ListOfInputs{ istream_iterator<string>{InputFile},{} };
	for (auto OneOrbit : ListOfInputs)
	{
		int pos_separator = OneOrbit.find(')');
		string CenterOfRotation = OneOrbit.substr(0, pos_separator);
		string Planet = OneOrbit.substr(pos_separator+1);
		OrbitDefintions[Planet] = CenterOfRotation;
		OrbitCounts[Planet] = 0;
	}


	
	string CurrentCenter = "COM";
	vector<string> SoFarInTheChain = { CurrentCenter };
	while (OrbitDefintions.size() != 0)
	{
		auto it = find_if(OrbitDefintions.begin(), OrbitDefintions.end(),
		[CurrentCenter](auto Definition) {return Definition.second == CurrentCenter; });
		if (it != OrbitDefintions.end())
		{
			int countincrement = OrbitCounts[CurrentCenter];
			CurrentCenter = OrbitDefintions.find((*it).first)->first;
			OrbitCounts[CurrentCenter] = countincrement +1;
			OrbitDefintions.erase(CurrentCenter);
			SoFarInTheChain.push_back(CurrentCenter);
		}
		else
		{
			auto test = find(SoFarInTheChain.rbegin(),SoFarInTheChain.rend(), CurrentCenter);
			CurrentCenter = *(test+1);
		}
	}


}
