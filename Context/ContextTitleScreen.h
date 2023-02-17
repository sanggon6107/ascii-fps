#pragma once

#include "IContext.h"

#define TITLE_W 90
#define TITLE_H 10
#define START_W 100
#define START_H 40
#define EXIT_W  100
#define EXIT_H  50



enum class TitleScreenText : int { kTitle, kStart, kExit, kTitleScreenTextSize };

class ContextTitleScreen : public IContext
{
public :
	ContextTitleScreen(int w, int h);
	ContextState Run() override;
	void PutText(wchar_t* screen, int w, int h, TitleScreenText text_type);
private:
	vector<vector<wstring>> text_list_;
};