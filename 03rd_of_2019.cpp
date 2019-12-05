#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include "DayHeaders.h"

using namespace std;

int MinimumDistance(vector<pair<int, int>> Input)
{
	vector<int> distances;
	for (auto pair : Input)
	{
		if (pair != make_pair(0, 0))
		{
			int dist = abs(pair.first) + abs(pair.second);
			distances.push_back(dist);

		}
	}
	return *min_element(distances.begin(),distances.end());
}

vector<pair<int,int>> WireCoordinates(string &Wire)
{
	// convert instructions to coordinates of visited houses
	// U is up
	// D is down
	// R is right
	// L is left
	vector<pair<int, int>> temp = { make_pair(0, 0) }; // initialize;
	pair<int, int> CurrentCoordinate = make_pair(0, 0);
	int pos = 0;
	pos = Wire.find(",");
	while ( pos != string::npos )
	{
		string OneDirection = Wire.substr(0, 1);
		int Amount = stoi(Wire.substr(1, pos - 1));
		Wire.erase(0, pos+1);
		pos = Wire.find(",");
		for (int inc = 1; inc <= Amount; inc++)
		{
			if (OneDirection == "L") CurrentCoordinate.first --;
			if (OneDirection == "R") CurrentCoordinate.first ++;
			if (OneDirection == "U") CurrentCoordinate.second ++;
			if (OneDirection == "D") CurrentCoordinate.second --;
			temp.push_back(CurrentCoordinate);
		}

	}
	return temp;
}

void Day_03(ifstream& InputFile)
{



	vector<string> WireInputs{ istream_iterator<string>{InputFile},{} };
	string WireOne = WireInputs.at(0);
	string WireTwo = WireInputs.at(1);
	auto WireOneCoordinates = WireCoordinates(WireOne);
	auto WireTwoCoordinates = WireCoordinates(WireTwo);

	// keep them unsorted for part 2
	auto WireOneCoordinatesPartTwo = WireOneCoordinates;
	auto WireTwoCoordinatesPartTwo = WireTwoCoordinates;

	sort(WireOneCoordinates.begin(), WireOneCoordinates.end());
	sort(WireTwoCoordinates.begin(), WireTwoCoordinates.end());
	
	int sizeint = min(WireOneCoordinates.size(), WireTwoCoordinates.size());
	vector<pair<int,int>> Intersections(sizeint);
	auto it = set_intersection(WireOneCoordinates.begin(), WireOneCoordinates.end(), WireTwoCoordinates.begin(), WireTwoCoordinates.end(), Intersections.begin());
	Intersections.resize(it - Intersections.begin());


	cout << "Minimal distance of the intersection is " << MinimumDistance(Intersections) << "!\n";

	// part2
	vector<int> AllDistances;
	for (auto Intersection : Intersections)
	{
		auto ItOne = find(WireOneCoordinatesPartTwo.begin(), WireOneCoordinatesPartTwo.end(), Intersection);
		auto ItTwo = find(WireTwoCoordinatesPartTwo.begin(), WireTwoCoordinatesPartTwo.end(), Intersection);
		int dist = distance(WireOneCoordinatesPartTwo.begin(), ItOne) + distance(WireTwoCoordinatesPartTwo.begin(), ItTwo);
		AllDistances.push_back(dist);
	}
	sort(AllDistances.begin(), AllDistances.end());
	
	cout << "Minimal number of steps from both wires to an intersection is " << AllDistances.at(1) << "!\n";

}
