#include "Cursor.h"

void Cursor::SetCursor(int title_screen_text_w, int title_screen_text_h)
{
	cursor_w_ = title_screen_text_w - static_cast<int>(wcslen(image_[0].data())) - horizontal_padding_;
	cursor_h_ = title_screen_text_h;
	if (cursor_w_ < 1) cursor_w_ = 1;
	if (cursor_h_ < 1) cursor_h_ = 1;
}

void Cursor::ShowCursor(wchar_t* screen)
{	
	for (int height = cursor_h_; height < cursor_h_ + static_cast<int>(image_.size()); height++)
	{
		wchar_t* char_to_put = image_[height - cursor_h_].data();
		for (int x_pos = 0; x_pos < wcslen(char_to_put); x_pos++)
		{
			screen[screen_width_ * height + cursor_w_ + x_pos] = image_[height - cursor_h_][x_pos];
		}
	}
}

Cursor::Cursor(int screen_width, int screen_height) : cursor_w_(0), cursor_h_(0), screen_width_(screen_width), screen_height_(screen_height), horizontal_padding_(HORIZONTAL_PADDING)
{
	image_.push_back(L"      █   ");
	image_.push_back(L"       ██ ");
	image_.push_back(L"██████████");
	image_.push_back(L"       ██ ");
	image_.push_back(L"      █   ");
}
