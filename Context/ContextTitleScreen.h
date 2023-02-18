#pragma once

#include "IContext.h"

//#define TITLE_W 90
//#define TITLE_H 10
//#define START_W 100
//#define START_H 40
//#define EXIT_W  100
//#define EXIT_H  50
//#define CUSOR_W 70

struct ObjectPosition
{
	int w_;
	int h_;
};

struct Cursor
{
	vector<wstring> image_;
	int horizontal_padding_{5};
};


enum class TitleScreenText : int { kTitle, kStart, kExit, kTitleScreenTextSize };

class ContextTitleScreen : public IContext
{
public :
	ContextTitleScreen(int w, int h);
	ContextState Run() override;
private:
	void PutText(wchar_t* screen, int w, int h, TitleScreenText text_type);
	void PutCorsur(wchar_t* screen, TitleScreenText text_type);

	vector<vector<wstring>> text_list_;
	Cursor cursor_;
	vector<ObjectPosition> text_position_;
};