#include "mapcreator.h"

using namespace std;

void MapCreator::Export(wstring& out)
{
	for (auto& row : map_)
	{
		for (auto& col : row)
		{
			out += col;
		}
	}
}

MapCreator::MapCreator(int w, int h) : w_(w), h_(h)
{
	InitMap();
	CreateMaze();
}

void MapCreator::InitMap()
{
	for (int row = 0; row < h_; row++)
	{
		map_.emplace_back(w_, L"#");

		if (row == 0 || row == h_ - 1 || row % 2 == 0) continue;

		for (int col = 1; col < w_ - 1; ++(++col)) { map_[row][col] = L"."; }
	}
}

void MapCreator::CreateMaze()
{
	int w = 1;
	int h = 1;
	
	int w_delta[4]{ 2, -2, 0, 0 };
	int h_delta[4]{ 0, 0, 2, -2 };

	for (int dir = CanMoveOn(); dir != Direction::disable;) // 0 ~ 3 : delta[0 ~ 3], 4 : impossible
	{
		int w_temp = w + w_delta[dir];
		int h_temp = h + h_delta[dir];
		if (w_temp <= 1 || w_temp >= w_ - 1) continue;
		if (h_temp <= 1 || h_temp >= h_ - 1) continue;
		
		map_[h + (h_delta[dir]/2)][w + (w_delta[dir]/2)] = L".";
		w = w_temp;
		h = h_temp;
	}
}

Direction CanMoveOn()
{
	int delta_idx[4]{ 0, 1, 2, 3 };

	random_device rd;
	mt19937 engine(rd());
	uniform_int_distribution<int> distribution(0, 3);

	return Direction::disable;
}
