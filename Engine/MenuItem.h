#pragma once
#include <memory>
#include <assert.h>
#include "Graphics.h"
#include "Rect.h"
#include "Mouse.h"
#include "Listener.h"
class MenuItem
{
public:
	virtual void Draw(Graphics& gfx) const = 0;
	virtual void Update(float dt, Mouse& mouse) = 0;
	virtual void MouseLeave() = 0;
	virtual void MouseIn(Mouse& mouse) = 0;
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
	int getData() { return data; }
	void addListener(Listener* newlistener) { listener = newlistener; }
	void setData(int newdata) { data = newdata; }
protected:
	MenuItem(VecF pos, float width, float height, Color color)
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
	int data = 0;
	Listener* listener = nullptr;
private:
};