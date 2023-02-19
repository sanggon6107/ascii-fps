#pragma once
#include <iostream>
#include <windows.h>
#include <wchar.h>
#include <string>
#include <chrono>
#include <cmath>
#include <array>
#include <ahadmin.h>
#include "../CommonLib/MapCreator.h"
#include "IContext.h"

using namespace std;

struct Player
{
	float x_;
	float y_;
	float ang_;
};

class ContextGamePlay : public IContext
{
public:
	ContextGamePlay(int screen_width, int screen_height);
	ContextState Run() override;
private:
	vector<int> wall_shades{ 0x2599, 0x2599, 0x256A, 0x253C, 0x253C, 0x250C, 0x250C, 0x2500, 0x2500, 0x2500, 0x2509, 0x2509, 0x2509, 0x2508, 0x2508, 0x2508, 0x2508 };
};