#pragma once
#include "Colors.h"
#include "Board.h"
#include "MenuItem.h"
class Menu
{
public:
	Menu(VecF pos, float width, float height, Color color)
		:
		pos(pos),
		width(width),
		height(height),
		color(color)
	{}
	void Draw(Graphics& gfx) const
	{
		gfx.DrawRectDim((VecI)pos, (int)width, (int)height, color);
		for (auto i : items)
		{
			i->Draw(gfx);
		}
	}
	void Update(float dt, Mouse& mouse)
	{
		for (auto i : items)
		{
			i->Update(dt, mouse);
		}
	}
	void MouseLeave()
	{
		for (auto i : items)
		{
			i->MouseLeave();
		}
	}
	void ProcessCommand(Mouse& mouse)
	{
		for (auto i : items)
		{
			if (i->GetRect().isContaint(mouse.GetPos()))
			{
				i->MouseIn(mouse);
			}
			else
			{
				i->MouseLeave();
			}
		}
		while (!mouse.IsEmpty())
		{
			mouse.Read();
		}
	}
	void AddItem(MenuItem* item, int data, Listener* listener) 
	{ 
		items.emplace_back(item);
		item->setData(data);
		item->addListener(listener);
	}
	RectF GetRect() { return RectF(pos, width, height); }
	VecF GetPos() { return pos; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }
private:
	VecF pos;
	float width;
	float height;
	Color color;
	std::vector<MenuItem*> items;
};