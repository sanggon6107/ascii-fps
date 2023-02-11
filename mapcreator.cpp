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

	for (int row = 0; row < h_; row++) { visited_.emplace_back(w_, false); }
}

void MapCreator::CreateMaze()
{
	random_device rd;
	mt19937 engine(rd());
	
	int w = 1;
	int h = 1;
	visited_[1][1] = true;
	
	while (1)
	{
		// Kill
		while (1) // 0 ~ 3 : delta[0 ~ 3], 4 : impossible
		{
			auto [dir, w_temp, h_temp] = CanMoveOn(engine, w, h);

			if (dir == Direction::disable) break;

			map_[h + (h_delta_[dir] / 2)][w + (w_delta_[dir] / 2)] = L".";
			w = w_temp;
			h = h_temp;
			visited_[h_temp][w_temp] = true;
		}
		// Hunt
		auto [next_w, next_h] = Hunt();
		if (next_w == 0 && next_h == 0) return;

		w = next_w;
		h = next_h;
		visited_[next_h][next_w] = true;
	}
}

tuple<Direction, int, int> MapCreator::CanMoveOn(mt19937 & engine, int w, int h)
{

	vector<int> candidate{};

	for (int dir = Direction::right; dir < Direction::disable; dir++)
	{
		int w_temp = w + w_delta_[dir];
		int h_temp = h + h_delta_[dir];
		if (w_temp <= 0 || w_temp >= w_ - 1)  continue;
		if (h_temp <= 0 || h_temp >= h_ - 1)  continue;
		if (visited_[h_temp][w_temp] == true) continue;
		candidate.push_back(dir);
	}
	
	if (candidate.size() == 0) return make_tuple(Direction::disable, w, h);
	uniform_int_distribution<int> distribution(0, candidate.size() - 1);

	int dir = candidate[distribution(engine)];

	return make_tuple(static_cast<Direction>(dir), w + w_delta_[dir], h + h_delta_[dir]);
}

tuple<int, int> MapCreator::Hunt()
{
	for (int h = 1; h < h_ - 1; ++(++h))
	{
		for (int w = 1; w < w_ - 1; ++(++w))
		{
			if (visited_[h][w] == true) continue;

			for (int dir = Direction::right; dir < Direction::disable; dir++)
			{
				int h_temp = h + h_delta_[dir];
				int w_temp = w + w_delta_[dir];
				if (w_temp <= 0 || w_temp >= w_ - 2)  continue;
				if (h_temp <= 0 || h_temp >= h_ - 2)  continue;
				if (visited_[h_temp][w_temp] == false) continue;
				
				map_[h + (h_delta_[dir] / 2)][w + (w_delta_[dir] / 2)] = L".";

				return make_tuple(w, h);
			}
		}
	}

	return make_tuple(0, 0);
}