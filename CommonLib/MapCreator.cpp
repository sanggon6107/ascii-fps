#include "MapCreator.h"

using namespace std;

void MapCreator::GetCurrentMapInfo(MapInfo& map_info)
{
	map_info.map_width_ = map_width_;
	map_info.map_height_ = map_height_;
	Export(map_info.map_);
}

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

MapCreator::MapCreator(int w, int h) : map_width_(w), map_height_(h) {}

void MapCreator::CreateMap(int w, int h)
{
	map_width_ = w;
	map_height_ = h;
	InitMap();
	CreateMaze();
}

void MapCreator::InitMap()
{
	visited_.clear();
	map_.clear();

	for (int row = 0; row < map_height_; row++)
	{
		map_.emplace_back(map_width_, L"#");

		if (row == 0 || row == map_height_ - 1 || row % 2 == 0) continue;

		for (int col = 1; col < map_width_ - 1; ++(++col)) { map_[row][col] = L"."; }
	}

	for (int row = 0; row < map_height_; row++) { visited_.emplace_back(map_width_, false); }
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
		if (w_temp <= 0 || w_temp >= map_width_ - 1)  continue;
		if (h_temp <= 0 || h_temp >= map_height_ - 1)  continue;
		if (visited_[h_temp][w_temp] == true) continue;
		candidate.push_back(dir);
	}
	
	if (candidate.size() == 0) return make_tuple(Direction::disable, w, h);
	uniform_int_distribution<int> distribution(0, static_cast<int>(candidate.size()) - 1);

	int dir = candidate[distribution(engine)];

	return make_tuple(static_cast<Direction>(dir), w + w_delta_[dir], h + h_delta_[dir]);
}

tuple<int, int> MapCreator::Hunt()
{
	for (int h = 1; h < map_height_ - 1; ++(++h))
	{
		for (int w = 1; w < map_width_ - 1; ++(++w))
		{
			if (visited_[h][w] == true) continue;

			for (int dir = Direction::right; dir < Direction::disable; dir++)
			{
				int h_temp = h + h_delta_[dir];
				int w_temp = w + w_delta_[dir];
				if (w_temp <= 0 || w_temp >= map_width_ - 1)  continue;
				if (h_temp <= 0 || h_temp >= map_height_ - 1)  continue;
				if (visited_[h_temp][w_temp] == false) continue;
				
				map_[h + (h_delta_[dir] / 2)][w + (w_delta_[dir] / 2)] = L".";

				return make_tuple(w, h);
			}
		}
	}

	return make_tuple(0, 0);
}