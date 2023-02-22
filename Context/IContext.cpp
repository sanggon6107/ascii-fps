#include "IContext.h"

ContextFactory::ContextFactory() {}

IContext::IContext()
{
	auto& screen_mgr = ScreenMgr::GetInstance();
	screen_width_ = screen_mgr.GetScreenWidth();
	screen_height_ = screen_mgr.GetScreenHeight();
	screen_ = screen_mgr.GetScreen();
}