#include "Game.h"

Game::Game()
{
	screen_mgr_ = make_unique<ScreenMgr>(SCREEN_WIDTH, SCREEN_HEIGHT);
	map_creator_ = make_unique<MapCreator>(MAP_WIDTH, MAP_HEIGHT);
	
}