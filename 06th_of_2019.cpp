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

	auto it = find_if(OrbitDefintions.begin(), OrbitDefintions.end(),
		[](auto Definition) {return Definition.second == "COM"; });

	// create chains:
	// while map.size != 0:
	// ?  chain = com initialize
	//
	// current = the one that does not exist in values, only in keys
	//......... chain.push_back(OrbitDefinitions[current])
	// .........erase current entry from map
	// if current not found in map, create new chain
	// new chain is initialized to whatever exists in previous chains until current
	// after initialization same loop as above...

	// then, count stuff
	// for (auto chain : Chains )
	// for each key:
	// orbits += distance[key,COM] - or easier, just the index of the vector
	


}
