#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <assert.h>
#include "Graphics.h"
#include "Rect.h"
#include "Mouse.h"
class IGui
{
public:
	virtual void Draw(Graphics& gfx) const = 0;
	virtual void Update(float dt, Mouse& mouse) = 0;
	virtual void AddItem(std::shared_ptr<IGui> item) = 0;
	virtual void MouseClick() = 0;
	virtual void MouseLeave() = 0;
	virtual void MouseIn() = 0;
	RectF GetRect()
	{
		return RectF(pos, width, height);
	}
	VecF GetPos()
	{
		return pos;
	}
	float GetWidth()
	{
		return width;
	}
	float GetHeight()
	{
		return height;
	}
protected:
	IGui(VecF pos, float width, float height, Color color)
		:
		pos(pos),
		width(width),
		height(height),
		color(color)
	{}
	VecF pos;
	float width;
	float height;
	Color color;
private:
};