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
	map <string, string> OrbitDefinitions;
	map <string, int> OrbitCounts;
	// parse input
	vector<string> ListOfInputs{ istream_iterator<string>{InputFile},{} };
	for (auto OneOrbit : ListOfInputs)
	{
		int pos_separator = OneOrbit.find(')');
		string CenterOfRotation = OneOrbit.substr(0, pos_separator);
		string Planet = OneOrbit.substr(pos_separator+1);
		OrbitDefinitions[Planet] = CenterOfRotation;
		OrbitCounts[Planet] = 0;
	}

	// part 2:
	vector<string> YouChain = {};
	vector<string> SantaChain = {};
	
	string LookingFor = "YOU";
	while ( OrbitDefinitions.find(LookingFor) != OrbitDefinitions.end())
	{
		LookingFor = OrbitDefinitions.find(LookingFor)->second;
		YouChain.push_back(LookingFor);
	}
	
	LookingFor = "SAN";
	while (OrbitDefinitions.find(LookingFor) != OrbitDefinitions.end())
	{
		LookingFor = OrbitDefinitions.find(LookingFor)->second;
		SantaChain.push_back(LookingFor);
	}
	
	sort(SantaChain.begin(), SantaChain.end());
	sort(YouChain.begin(), YouChain.end());
	vector<string> ToTheMergebase(SantaChain.size()+YouChain.size());
	auto diff = set_symmetric_difference(SantaChain.begin(), SantaChain.end(), YouChain.begin(), YouChain.end(),ToTheMergebase.begin());
	ToTheMergebase.resize(diff - ToTheMergebase.begin());
	int DistanceYouToSanta = ToTheMergebase.size();
	
	// part 1:
	string CurrentCenter = "COM";

	vector<string> SoFarInTheChain = { CurrentCenter };
	while (OrbitDefinitions.size() != 0)
	{
		auto it = find_if(OrbitDefinitions.begin(), OrbitDefinitions.end(),
		[CurrentCenter](auto Definition) {return Definition.second == CurrentCenter; });
		if (it != OrbitDefinitions.end())
		{
			int countincrement = OrbitCounts[CurrentCenter];
			CurrentCenter = OrbitDefinitions.find((*it).first)->first;
			OrbitCounts[CurrentCenter] = countincrement +1;
			OrbitDefinitions.erase(CurrentCenter);
			SoFarInTheChain.push_back(CurrentCenter);
		}
		else
		{
			auto test = find(SoFarInTheChain.rbegin(),SoFarInTheChain.rend(), CurrentCenter);
			CurrentCenter = *(test+1);
		}
	}

	int TotalOrbitalCount = accumulate(OrbitCounts.begin(), OrbitCounts.end()
		,0, [](int value,auto p) { return value + p.second; });

	cout << "The total count of orbits in this system is: " << TotalOrbitalCount << "!\n";
// Part 1: 273985
	cout << "The total count of orbits between you and Santa is: " << DistanceYouToSanta << "!\n";
// Part 2: 460
}
