#pragma once
#include "Vec2.h"
class Camera
{
public:
	Camera(const VecF& pos)
		:
		pos(pos)
	{}
	void MoveBy(const VecF& offset)
	{
		pos += offset;
	}
	void MoveTo(const VecF& newPos)
	{
		pos = newPos;
	}
	VecI GetPos() const
	{
		return pos;
	}
private:
	VecF pos;
};