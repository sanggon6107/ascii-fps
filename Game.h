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
	
private :
	vector<unique_ptr<IContext>> context_;
};
