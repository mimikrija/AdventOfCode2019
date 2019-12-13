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

class Moon
{
public:
	Moon(int x, int y, int z);
	~Moon();
	

private:
	int xpos, ypos, zpos, xvel, yvel, zvel;

};

Moon::Moon(int x, int y, int z)
{
	xpos = x;
	ypos = y;
	zpos = z;
}

Moon::~Moon()
{
}

void Day_12(ifstream& InputFile)
{
	// I am
	//<x = -3, y = 15, z = -11>
	//	<x = 3, y = 13, z = -19>
	//	<x = -13, y = 18, z = -2>
	//	<x = 6, y = 0, z = -1>
	// parse input
	vector<Moon> Moons;
	Moons.push_back(Moon(-3, 15, -11));
	Moons.push_back(Moon(3, 13, -19));
	Moons.push_back(Moon(-13, 18, -2));
	Moons.push_back(Moon(6, 0, -1));

}