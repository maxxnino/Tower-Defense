#pragma once
#include "Colors.h"
#include "Board.h"
#include "MenuItem.h"
#include "Observer.h"
#include "MouseState.h"
class Menu : public Observer, public IObervable
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
	void OnNotify(void* datauser) override {};
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
	void ProcessCommand(Mouse& mouse, MouseState& mouseTower)
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
			if (mouse.Read().GetType() == Mouse::Event::Type::RPress)
			{
				mouseTower.data = 0;
			}
		}
	}
	void AddItem(MenuItem* item, int data, IObervable* obs) 
	{ 
		items.emplace_back(item);
		item->setData(data);
		item->AddObs(obs);
	}
	void AddItem(MenuItem* item, int data)
	{
		items.emplace_back(item);
		item->setData(data);
	}
	void ResetItem()
	{
		for (auto i : items)
		{
			i->ResetState();
		}
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