#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

enum Direction { right = 0, left = 1, down = 2, up = 3, disable = 4 };


class MapCreator
{
public :
	void Export(wstring& out);

private:
	MapCreator(int w, int h);
	void InitMap();
	void CreateMaze();
	
	
	vector<vector<wstring>> map_;
	int w_;
	int h_;
};