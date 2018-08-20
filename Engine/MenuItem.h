#pragma once
#include <memory>
#include <assert.h>
#include "Graphics.h"
#include "Rect.h"
#include "Mouse.h"
#include "Observer.h"
class MenuItem : public Observer, public IObervable
{
public:
	virtual void Draw(Graphics& gfx) const = 0;
	virtual void Update(float dt, Mouse& mouse) = 0;
	virtual void MouseLeave() = 0;
	virtual void MouseIn(Mouse& mouse) = 0;
	virtual void ResetState() = 0;
	void OnNotify(void* datauser) override {};
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
	void* getData() { return data; }
	void setData(void* newdata) { data = newdata; }
	void setColor(Color c)
	{
		color = c;
		baseColor = c;
	}
protected:
	MenuItem(VecF pos, float width, float height)
		:
		pos(pos),
		width(width),
		height(height)
	{}
	VecF pos;
	float width;
	float height;
	Color color;
	Color baseColor;
	void* data;
private:
};