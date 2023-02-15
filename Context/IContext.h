#pragma once

enum class ContextState { kContextGamePlay, kContextTitleScreen, kContextExit };

class IContext
{
public:
	IContext();
	virtual ContextState Run() = 0;
private:

};