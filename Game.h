#pragma once
#include <memory>
#include "CommonLib/MapCreator.h"
#include "CommonLib/ScreenMgr.h"
#include "CommonLib/CommonUtil.h"

#include "Context/IContext.h"


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

