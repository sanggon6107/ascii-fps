#pragma once
#include <vector>
#include <string>
using namespace std;

class MapCreator
{
	MapCreator(int w, int h);
	void Create(int w, int h);
	vector<vector<wstring>> Export();
	
	vector<vector<wstring>> map_;
};