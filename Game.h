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
	void Launch();
private :
	vector<shared_ptr<IContext>> context_;
	shared_ptr<IContext> current_context_state_;
};

