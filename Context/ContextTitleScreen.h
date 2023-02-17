#pragma once

#include "IContext.h"

enum class TitleScreenText : int { kTitle, kTitleScreenTextSize };

class ContextTitleScreen : public IContext
{
public :
	ContextTitleScreen(int w, int h);
	ContextState Run() override;
	void PutText(wchar_t* screen, int w, int h, TitleScreenText text_type);
private:
	vector<vector<wstring>> text_list_;
};