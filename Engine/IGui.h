#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <assert.h>
#include "Graphics.h"
#include "Rect.h"
class IGui
{
public:
	virtual void Draw(Graphics& gfx) const = 0;
	virtual void Update(float dt) = 0;
	virtual void AddItem(std::shared_ptr<IGui> item) = 0;
	virtual void OnNotify() = 0;
	int GetID()
	{
		return ID;
	}
	RectF GetRect()
	{
		return RectF(pos, width, height);
	}
	VecF GetPos()
	{
		return pos;
	}
protected:
	IGui(int id, VecF pos, float width, float height, Color color)
		:
		ID(id),
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
	int ID = -1;
};