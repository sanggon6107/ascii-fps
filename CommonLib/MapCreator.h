#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "ScreenMgr.h"

using namespace std;

enum Direction : int { right = 0, left = 1, down = 2, up = 3, disable = 4 };

struct MapInfo
{
	int map_width_;
	int map_height_;
	wstring map_;
};


class MapCreator
{
public :
	MapCreator(int w, int h);
	
	void GetCurrentMapInfo(MapInfo& map_info);
private:
	void InitMap();
	void CreateMaze();
	void Export(wstring& out);
	tuple<Direction, int, int> CanMoveOn(mt19937& engine, int w, int h);
	tuple<int, int> Hunt();
	
	vector<vector<wstring>> map_;
	vector<vector<bool>> visited_;
	int map_width_;
	int map_height_;

	int w_delta_[4]{ 2, -2, 0, 0 };
	int h_delta_[4]{ 0, 0, 2, -2 };

};