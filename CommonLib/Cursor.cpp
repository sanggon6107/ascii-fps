#include "Cursor.h"

void Cursor::SetCursor(int title_screen_text_w, int title_screen_text_h)
{
	cursor_w_ = title_screen_text_w - static_cast<int>(wcslen(image_[0].data())) - horizontal_padding_;
	cursor_h_ = title_screen_text_h;
}

void Cursor::ShowCursor(wchar_t* screen)
{
	const int top = cursor_h_;
	int left = cursor_w_;

	if (left < 1) left = 1;
	
	for (int height = top; height < top + static_cast<int>(image_.size()); height++)
	{
		wchar_t* char_to_put = image_[height - top].data();
		wcscpy_s(&screen[screen_width_ * height + left], wcslen(char_to_put) + 1, char_to_put);
	}
}

Cursor::Cursor(int screen_width, int screen_height) : cursor_w_(0), cursor_h_(0), screen_width_(screen_width), screen_height_(screen_height), horizontal_padding_(HORIZONTAL_PADDING)
{
	image_.push_back(L"──────█───");
	image_.push_back(L"───────██─");
	image_.push_back(L"██████████");
	image_.push_back(L"───────██─");
	image_.push_back(L"──────█───");
}
