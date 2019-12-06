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
	// parse input
	vector<string> ListOfInputs{ istream_iterator<string>{InputFile},{} };
	for (auto OneOrbit : ListOfInputs)
	{
		int pos_separator = OneOrbit.find(')');
		string CenterOfRotation = OneOrbit.substr(0, pos_separator);
		string Planet = OneOrbit.substr(pos_separator+1);
		OrbitDefintions[Planet] = CenterOfRotation;

	}

	auto it = find_if(OrbitDefintions.begin(), OrbitDefintions.end(),
		[](auto Definition) {return Definition.second == "COM"; });

}
