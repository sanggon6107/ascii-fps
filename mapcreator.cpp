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
	for (int i = 0; i < h_; i++)
	{
		wstring row_temp = L"";
		for (int i = 0; i < w_; i++) { row_temp += L"#"; }
		map_.emplace_back(move(row_temp));
	}
}


void MapCreator::CreateMaze()
{
	int w = 1;
	int h = 1;
	
	int w_delta[4]{ 1, -1, 0, 0 };
	int h_delta[4]{ 0, 0, 1, -1 };
	int delta_idx[4]{ 0, 1, 2, 3 };

	random_device rd;
	mt19937 engine(rd());
	uniform_int_distribution<int> distribution(0, 3);
	cout << distribution(engine) << endl;
	
}

