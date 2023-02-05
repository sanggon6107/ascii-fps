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
	for (auto& row : map_) { row = L'#' + (L'.' * w_ - 2) + L'#'; }

	map_[0]               = L'#' * w_;
	map_[map_.size() - 1] = L'#' * w_;

}


void MapCreator::CreateMaze()
{

}

