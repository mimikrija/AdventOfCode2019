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
	void UpdateGravity();
	int TotalEnergy();
	int xpos, ypos, zpos, xvel = 0, yvel = 0, zvel = 0;
	int xvelnew = 0, yvelnew = 0, zvelnew = 0;


	bool operator==(const Moon& m) {
		return (xpos == m.xpos && ypos == m.ypos && zpos == m.zpos &&
				xvel == m.xvel && yvel == m.yvel && zvel == m.zvel);
	}

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
	xpos += xvel;
	ypos += yvel;
	zpos += zvel;
}

int Moon::TotalEnergy()
{
	Potential = abs(xpos) + abs(ypos) + abs(zpos);
	Kinetic = abs(xvel) + abs(yvel) + abs(zvel);
	return Potential * Kinetic;
}

void Moon::UpdateGravity()
{
	xvel += xvelnew;
	yvel += yvelnew;
	zvel += zvelnew;

	xvelnew = 0;
	yvelnew = 0;
	zvelnew = 0;
}

void ApplyGravity(Moon &MoonOne, Moon &MoonTwo)
{
	if (MoonOne.xpos > MoonTwo.xpos)
	{
		MoonOne.xvelnew--;
		MoonTwo.xvelnew++;
	}
	if (MoonOne.xpos < MoonTwo.xpos)
	{
		MoonOne.xvelnew++;
		MoonTwo.xvelnew--;
	}

	if (MoonOne.ypos > MoonTwo.ypos)
	{
		MoonOne.yvelnew--;
		MoonTwo.yvelnew++;
	}
	if (MoonOne.ypos < MoonTwo.ypos)
	{
		MoonOne.yvelnew++;
		MoonTwo.yvelnew--;
	}

	if (MoonOne.zpos > MoonTwo.zpos)
	{
		MoonOne.zvelnew--;
		MoonTwo.zvelnew++;
	}
	if (MoonOne.zpos < MoonTwo.zpos)
	{
		MoonOne.zvelnew++;
		MoonTwo.zvelnew--;
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

	vector<Moon>OriginalConstelation;
	OriginalConstelation.push_back(Moon(-3, 15, -11));
	OriginalConstelation.push_back(Moon(3, 13, -19));
	OriginalConstelation.push_back(Moon(-13, 18, -2));
	OriginalConstelation.push_back(Moon(6, 0, -1));

	int OriginalEnergy = 0;
	for (auto& Moon : OriginalConstelation)
	{
		OriginalEnergy += Moon.TotalEnergy();
	}

	//Moons.push_back(Moon(-1, 0, 2));
	//Moons.push_back(Moon(2, -10, -7));
	//Moons.push_back(Moon(4, -8, 8));
	//Moons.push_back(Moon(3, 5, -1));

	vector<pair<int, int>> Combinations{
	make_pair(0,1),
	make_pair(0,2),
	make_pair(0,3),
	make_pair(1,2),
	make_pair(1,3),
	make_pair(2,3)
	};


	unsigned long long int PartTwo = 0;
	for (int time = 1; time <= 1000; time++)
	{
		for (auto Combo : Combinations)
		{
			ApplyGravity(Moons.at(Combo.first), Moons.at(Combo.second));
		}
		for (auto &Moon : Moons)
		{
			Moon.UpdateGravity();
			Moon.ApplyVelocity();
		}

		for (int index = 0; index < 4; index++)
		{
			if (!(Moons.at(index) == OriginalConstelation.at(index))) continue;
			else PartTwo = time;
		}

	}

//	int TotalEnergy = accumulate(Moons.begin(), Moons.end(), [](auto Moon) {return Moon.TotalEnergy()}, 0);
	int TotalEnergy = 0;

	for (auto &Moon : Moons)
	{
		TotalEnergy += Moon.TotalEnergy();
	}

	cout << "Total energy is " << TotalEnergy << "!\n";
	// should time, energy and part two be long int??
	long long int time = 1000;
	vector<long long int> Matchesx(4, 0), Matchesy(4,0), Matchesz(4,0);
	while ( find(Matchesx.begin(),Matchesx.end(),0) != Matchesx.end()
		|| find(Matchesy.begin(), Matchesy.end(), 0) != Matchesy.end()
		|| find(Matchesz.begin(), Matchesz.end(), 0) != Matchesz.end()
		)
	{
		time++;
		for (auto Combo : Combinations)
		{
			ApplyGravity(Moons.at(Combo.first), Moons.at(Combo.second));
		}
		for (auto& Moon : Moons)
		{
			Moon.UpdateGravity();
			Moon.ApplyVelocity();
		}

		for (int index = 0; index < 4; index++)
		{
			if (Moons.at(index).xpos == OriginalConstelation.at(index).xpos &&
				Moons.at(index).xvel == OriginalConstelation.at(index).xvel)
			{
				Matchesx.at(index) = time;
			}

			if (Moons.at(index).ypos == OriginalConstelation.at(index).ypos &&
				Moons.at(index).yvel == OriginalConstelation.at(index).yvel)
			{
				Matchesy.at(index) = time;
			}

			if (Moons.at(index).zpos == OriginalConstelation.at(index).zpos &&
				Moons.at(index).zvel == OriginalConstelation.at(index).zvel)
			{
				Matchesz.at(index) = time;
			}
		}
	}
	long long int LCMx, LCMy, LCMz;
	LCMx = lcm(lcm(lcm(Matchesx.at(0), Matchesx.at(1)), Matchesx.at(2)), Matchesx.at(3));
	LCMy = lcm(lcm(lcm(Matchesy.at(0), Matchesy.at(1)), Matchesy.at(2)), Matchesy.at(3));
	LCMz = lcm(lcm(lcm(Matchesz.at(0), Matchesz.at(1)), Matchesz.at(2)), Matchesz.at(3));

	PartTwo = lcm(lcm(LCMx, LCMy), LCMz);
		
	cout << "They align after " << PartTwo << " timesteps!\n";

	// Part2 10905535414612983616 not correct
	// Part2  1443288054496335952 not correct

}