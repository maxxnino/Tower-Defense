#pragma once
#include "Vec2.h"
class Camera
{
public:
	Camera(const VecF& pos, float width, float height)
		:
		pos(pos),
		width(width),
		height(height)
	{}
	void MoveBy(const VecF& offset)
	{
		pos += offset;
		pos.x = std::min(pos.x, -extentBoard.left);
		pos.y = std::min(pos.y, -extentBoard.top);
		pos.x = std::max(pos.x, -extentBoard.right + width);
		pos.y = std::max(pos.y, -extentBoard.bottom + height);
	}
	void MoveTo(const VecF& newPos)
	{
		pos = newPos;
		pos.x = std::min(pos.x, -extentBoard.left);
		pos.y = std::min(pos.y, -extentBoard.top);
		pos.x = std::max(pos.x, -extentBoard.right + width);
		pos.y = std::max(pos.y, -extentBoard.bottom + height);
	}
	VecI GetPos() const
	{
		return pos;
	}
	void SetExtend(const RectF& extend)
	{
		extentBoard = extend;
	}
	RectF GetRect() const
	{
		return RectF(pos * -1.0f,width,height);
	}
private:
	VecF pos;
	float width;
	float height;
	RectF extentBoard;
};