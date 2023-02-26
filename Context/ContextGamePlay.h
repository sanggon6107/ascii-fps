#pragma once
#include <iostream>
#include <windows.h>
#include <wchar.h>
#include <string>
#include <chrono>
#include <cmath>
#include <array>
#include <ahadmin.h>

#include "../CommonLib/MapCreator.h"
#include "../CommonLib/Mouse.h"
#include "IContext.h"

enum class CharactorDirection { kForward, kBackward, kLeft, kRight };

constexpr int kMiniMapWidth = 17;
constexpr int kMiniMapHeight = 17;

using namespace std;

struct Player
{
	float x_;
	float y_;
	float ang_;
};

class ContextGamePlay : public IContext
{
public:
	ContextGamePlay();
	ContextState Run() override;
private:
	void MoveOnUserKeyUpdate(Player& player, MapInfo& map_info, float elapsed_time, CharactorDirection charactor_direction);
	void MoveOnUserMouseUpdate(Player& player);
	void SetMouseToZero();
	void InitStage(Player& player, MapInfo& map_info, shared_ptr<MapCreator> map_creator);
	void ShowFrame(MapInfo& map_info, Player& player, ScreenMgr& screen_mgr);

	vector<int> wall_shades_{ 0x2599, 0x2599, 0x256A, 0x253C, 0x253C, 0x250C, 0x250C, 0x2500, 0x2500, 0x2500, 0x2509, 0x2509, 0x2509, 0x2508, 0x2508, 0x2508, 0x2508 };
	Mouse mouse_;
	int current_stage_;
	int map_width_unit_;
	int map_height_unit_;

	DECLARE_CONTEXT_FACTORY(ContextGamePlay)
};
IMPLEMENT_CONTEXT_FACTORY(ContextState::kContextGamePlay, ContextGamePlay)