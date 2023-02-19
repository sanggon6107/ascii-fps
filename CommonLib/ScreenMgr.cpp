#include "ScreenMgr.h"

ScreenMgr::ScreenMgr(int screen_width, int screen_height) : screen_width_(screen_width), screen_height_(screen_height), bytes_written_(0)
{
	screen_ = make_unique<wchar_t[]>(screen_width_ * screen_height_);
	console_ = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console_);
}


void ScreenMgr::Show()
{
	screen_[screen_width_ * screen_height_ - 1] = '\0';
	WriteConsoleOutputCharacter(console_, screen_.get(), screen_width_ * screen_height_, {0, 0}, &bytes_written_);
}
