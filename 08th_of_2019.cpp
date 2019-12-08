#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "DayHeaders.h"


using namespace std;
void Day_08(ifstream& InputFile)
{
	vector<char> Pixels;
	char Digit;
	while (InputFile >> Digit)
	{
		Pixels.push_back(Digit);
	}

// The image you received is 25 pixels wide and 6 pixels tall.
	vector<vector<char>> Layers;
	vector<int> zerocounts;
	for (int LayerCount = 0; LayerCount < Pixels.size() / (25 * 6); LayerCount++)
	{
		vector<char> OneLayer = {};
		for (int PixelsInLayer = 0; PixelsInLayer < 25 * 6; PixelsInLayer++)
		{
			OneLayer.push_back(Pixels.at(LayerCount*25*6+PixelsInLayer));
		}
		Layers.push_back(OneLayer);
		zerocounts.push_back(count(OneLayer.begin(),OneLayer.end(),'0'));
	}

	int TheLayer = distance(zerocounts.begin(), min_element(zerocounts.begin(), zerocounts.end())) ;
	int countones = count((Layers.at(TheLayer)).begin(), (Layers.at(TheLayer)).end(),'1');
	int counttwos = count((Layers.at(TheLayer)).begin(), (Layers.at(TheLayer)).end(),'2');
	
	cout << "Part one solution is: " << countones * counttwos << "!\n";
	// 1524 too low
}