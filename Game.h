#pragma once
#include <vector>
#include "CommonLib/MapCreator.h"
#include "CommonLib/ScreenMgr.h"
#include "Context/IContext.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 80

#define MAP_WIDTH 17
#define MAP_HEIGHT 17

using namespace std;

class Game
{
public :
	Game();
	
public :
	unique_ptr<ScreenMgr> screen_mgr_;
	unique_ptr<MapCreator> map_creator_;
	vector<unique_ptr<IContext>> context_;
};