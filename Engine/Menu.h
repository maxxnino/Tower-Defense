#pragma once
#include "Codex.h"
#include "Button.h"
class Menu
{
public:
	Menu(VecF pos, float width, float height, const std::shared_ptr<Surface> surf)
		:
		pos(pos),
		width(width),
		height(height),
		surf(surf)
	{}
	void Draw(Graphics& gfx) const noexcept
	{
		//gfx.DrawRectDim((VecI)pos, (int)width, (int)height, color);
		gfx.DrawSprite((int)pos.x, (int)pos.y, *surf, SpriteEffect::Copy{});
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
	}	
	void AddItem(Button* item)
	{
		items.emplace_back(item);
	}
	void ResetItem()
	{
		for (auto i : items)
		{
			i->ResetState();
		}
	}
	inline RectF GetRect() { return RectF(pos, width, height); }
	inline VecF GetPos() { return pos; }
	inline float GetWidth() { return width; }
	inline float GetHeight() { return height; }
private:
	VecF pos;
	float width;
	float height;
	const std::shared_ptr<Surface> surf;
	std::vector<Button*> items;
};