#pragma once

enum class ContextState { kContextGamePlay, kContextTitleScreen, kContextExit };

class IContext
{
public :
	virtual ContextState Run() = 0;

protected :
	IContext(int w, int h);

private :
	int h_;
	int w_;
};