#pragma once
#include <windows.h>
#include <wchar.h>
#include <string>
#include <iostream>

using namespace std;

enum class ContextState { kContextGamePlay, kContextTitleScreen, kContextExit };

class IContext
{
public :
	virtual ContextState Run() = 0;

protected :
	IContext(int w, int h);

	int h_;
	int w_;
};