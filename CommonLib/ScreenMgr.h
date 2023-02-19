#pragma once
#include <Windows.h>
#include <memory>

using namespace std;

class ScreenMgr
{
public :
	ScreenMgr(int screen_width, int screen_height_);
	void Show();
private :
	unique_ptr<wchar_t[]> screen_;
	HANDLE console_;
	DWORD bytes_written_;
	
	int screen_width_;
	int screen_height_;
};