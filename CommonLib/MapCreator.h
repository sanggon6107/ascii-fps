#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

enum Direction : int { right = 0, left = 1, down = 2, up = 3, disable = 4 };


class MapCreator
{
public :
	MapCreator(int w, int h);
	void Export(wstring& out);

private:
	void InitMap();
	void CreateMaze();
	tuple<Direction, int, int> CanMoveOn(mt19937& engine, int w, int h);
	tuple<int, int> Hunt();
	
	vector<vector<wstring>> map_;
	vector<vector<bool>> visited_;
	int w_;
	int h_;

	int w_delta_[4]{ 2, -2, 0, 0 };
	int h_delta_[4]{ 0, 0, 2, -2 };

};