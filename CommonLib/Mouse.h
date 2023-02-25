#pragma once
#include <windows.h>
#include <tuple>

using namespace std;

class Mouse
{
public :
	Mouse();
	tuple<int, int> GetMousePos();
	tuple<int, int> DetectMouseMovement();
	void SetMousePos(int x, int y);
	void UpdateMousePosInfo();
private :
	int x_;
	int y_;
	POINT point_;
};