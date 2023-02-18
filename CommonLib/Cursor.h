#pragma once

#include <string>
#include <vector>
using namespace std;

#define HORIZONTAL_PADDING 10

class Cursor
{
public :
	Cursor(int screen_width, int screen_height);
	void SetCursor(int title_screen_text_w, int title_screen_text_h);
	void ShowCursor(wchar_t* screen);
	
private :
	int horizontal_padding_;
	vector<wstring> image_;
	int cursor_w_;
	int cursor_h_;
	int screen_width_;
	int screen_height_;
};