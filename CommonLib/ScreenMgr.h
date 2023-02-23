#pragma once
#include <Windows.h>
#include <memory>
#include "CommonUtil.h"

using namespace std;

class ScreenMgr
{
	MAKE_SINGLETON(ScreenMgr)
public :
	void Show();
	int GetScreenWidth() { return screen_width_; }
	int GetScreenHeight() { return screen_height_; }
	shared_ptr<wchar_t[]> GetScreen() { return screen_; }
private :
	shared_ptr<wchar_t[]> screen_;
	HANDLE console_;
	DWORD bytes_written_;
	
	int screen_width_;
	int screen_height_;
};