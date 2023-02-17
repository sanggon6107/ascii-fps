#pragma once
#include <windows.h>
#include <wchar.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum class ContextState { kContextGamePlay, kContextTitleScreen, kContextExit };

class IContext
{
public :
	virtual ContextState Run() = 0;
	virtual ~IContext() {}
protected :
	IContext(int w, int h);

	int screen_height_;
	int screen_width_;
};