#pragma once
#include <unordered_set>
#include "Rect.h"
#include "Graphics.h"
#include "IGui.h"
#include "Mouse.h"
template <typename Entity>
class _Tile
{
public:
	void MouseClick(const VecI& mousePos)
	{
		for (auto i : items)
		{
			if (i->GetRect().isContaint(mousePos))
			{
				i->MouseClick();
			}
		}
	}
	void MouseMove(const VecI& mousePos)
	{
		for (auto i : items)
		{
			if (i->GetRect().isContaint(mousePos))
			{
				i->MouseIn();
			}
			else
			{
				i->MouseLeave();
			}
		}
	}
	void AddItem(std::shared_ptr<Entity> sub)
	{
		items.emplace_back(sub);
	}
	void Awake()
	{
		c = Colors::Red;
	}
	void Sleep()
	{
		c = Colors::Blue;
	}
	void Draw(Graphics& gfx, VecI pos,int width, int height) const
	{
		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
	}
private:
	std::vector<std::shared_ptr<Entity>> items;
	Color c = Colors::Blue;
};