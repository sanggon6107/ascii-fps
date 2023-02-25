#include "Mouse.h"

Mouse::Mouse()
{
	GetCursorPos(&point_);
	x_ = static_cast<int>(point_.x);
	y_ = static_cast<int>(point_.y);
}

tuple<int, int> Mouse::GetMousePos(){ return make_tuple(x_, y_); }

tuple<int, int> Mouse::DetectMouseMovement()
{
	GetCursorPos(&point_);

	tuple<int, int> delta = make_tuple(static_cast<int>(point_.x) - x_, static_cast<int>(point_.y) - y_);

	x_ = static_cast<int>(point_.x);
	y_ = static_cast<int>(point_.y);

	return delta;
}

void Mouse::SetMousePos(int x, int y)
{
	SetCursorPos(x, y);
}

void Mouse::UpdateMousePosInfo()
{
	GetCursorPos(&point_);
	x_ = static_cast<int>(point_.x);
	y_ = static_cast<int>(point_.y);
}