#pragma once
#include "IContext.h"

class ContextTitleScreen : public IContext
{
public :
	ContextTitleScreen(int w, int h);
	ContextState Run() override;
	void WriteText();
private:
};