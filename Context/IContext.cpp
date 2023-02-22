#include "IContext.h"

ContextFactory::ContextFactory() {}

IContext::IContext() : screen_mgr_(&ScreenMgr::GetInstance())
{
	screen_width_ = screen_mgr_->GetScreenWidth();
	screen_height_ = screen_mgr_->GetScreenHeight();
	screen_ = screen_mgr_->GetScreen();
}