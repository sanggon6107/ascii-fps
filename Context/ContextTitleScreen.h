#pragma once

#include "IContext.h"
#include "../CommonLib/Cursor.h"

struct ObjectPosition
{
	int w_;
	int h_;
};


enum class TitleScreenText : int { kTitle, kStart, kExit, kTitleScreenTextSize };

class ContextTitleScreen : public IContext
{
public :
	ContextTitleScreen();
	ContextState Run() override;
private:
	void PutText(int w, int h, TitleScreenText text_type);

	vector<vector<wstring>> text_list_;
	Cursor cursor_;
	vector<ObjectPosition> text_position_;

	DECLARE_CONTEXT_FACTORY(ContextTitleScreen)
};
IMPLEMENT_CONTEXT_FACTORY(ContextState::kContextTitleScreen, ContextTitleScreen)