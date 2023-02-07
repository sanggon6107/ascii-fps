#include "mapcreator.h"

using namespace std;

void MapCreator::Export(wstring& out)
{
	for (auto& row : map_) { out += row; }
}

MapCreator::MapCreator(int w, int h) : w_(w), h_(h)
{
	InitMap();
	CreateMaze();
}

void MapCreator::InitMap()
{
	vector<wstring> map_element{ L"#", L"." };

	for (int i = 0; i < h_; i++)
	{
		wstring row_temp = L"";
		if (i == 0 || i == h_ - 1)
		{
			for (int col = 0; col < w_; col++) { row_temp += L"#"; }
			map_.push_back(move(row_temp));
		}
		else
		{
			row_temp += L"#";
			for (int col = 1; col < w_ - 1; col++) { row_temp += map_element[col % 2]; }
			row_temp += L"#";
			map_.push_back(move(row_temp));
		}
	}
}

void MapCreator::CreateMaze()
{
	int w = 1;
	int h = 1;
	
	int w_delta[4]{ 1, -1, 0, 0 };
	int h_delta[4]{ 0, 0, 1, -1 };

	for (int dir = CanMoveOn(); dir != Direction::disable;) // 0 ~ 3 : delta[0 ~ 3], 4 : impossible
	{
		int w_temp = w + w_delta[dir];
		int h_temp = h + h_delta[dir];
		if (w_temp <= 1 || w_temp >= w_ - 1) continue;
		if (h_temp <= 1 || h_temp >= h_ - 1) continue;

		map_[h_temp].replace(w_temp, 1, L".");
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
