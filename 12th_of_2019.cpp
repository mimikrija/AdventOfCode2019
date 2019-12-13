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
	void ApplyVelocity();
	int TotalEnergy();
	int xpos, ypos, zpos, xvel = 0, yvel = 0, zvel = 0;

private:
	int Kinetic = 0, Potential = 0;

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

void Moon::ApplyVelocity()
{
	xvel += xpos;
	yvel += ypos;
	zvel += zpos;
}

int Moon::TotalEnergy()
{
	Potential = abs(xpos) + abs(ypos) + abs(zpos);
	Kinetic = abs(xvel) + abs(yvel) + abs(zvel);
	return Potential + Kinetic;
}
void ApplyGravity(Moon &MoonOne, Moon &MoonTwo)
{
	if (MoonOne.xpos > MoonTwo.xpos)
	{
		MoonOne.xvel--;
		MoonTwo.xvel++;
	}
	if (MoonOne.xpos < MoonTwo.xpos)
	{
		MoonOne.xvel++;
		MoonTwo.xvel--;
	}

	if (MoonOne.ypos > MoonTwo.ypos)
	{
		MoonOne.yvel--;
		MoonTwo.yvel++;
	}
	if (MoonOne.ypos < MoonTwo.ypos)
	{
		MoonOne.yvel++;
		MoonTwo.yvel--;
	}

	if (MoonOne.zpos > MoonTwo.zpos)
	{
		MoonOne.zvel--;
		MoonTwo.zvel++;
	}
	if (MoonOne.zpos < MoonTwo.zpos)
	{
		MoonOne.zvel++;
		MoonTwo.zvel--;
	}
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

	vector<pair<int, int>> Combinations{
	make_pair(0,1),
	make_pair(0,2),
	make_pair(0,3),
	make_pair(1,2),
	make_pair(1,3),
	make_pair(2,3)
	};



	for (int time = 1; time <= 1000; time++)
	{
		for (auto Combo : Combinations)
		{
			ApplyGravity(Moons.at(Combo.first), Moons.at(Combo.second));
		}
		for (auto Moon : Moons) Moon.ApplyVelocity();

	}

//	int TotalEnergy = accumulate(Moons.begin(), Moons.end(), [](auto Moon) {return Moon.TotalEnergy()}, 0);
	int TotalEnergy = 0;

	for (auto Moon : Moons)
	{
		TotalEnergy += Moon.TotalEnergy();
	}

	cout << "Total energy is " << TotalEnergy << "!\n";
}