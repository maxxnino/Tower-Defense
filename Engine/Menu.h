#pragma once
#include "Colors.h"
#include "MenuItem.h"
#include "MouseState.h"
class Menu
{
public:
	Menu(VecF pos, float width, float height, Color color);
	void Draw(Graphics& gfx) const noexcept;
	void Update(float dt, Mouse& mouse) noexcept;
	void MouseLeave() noexcept;
	void ProcessCommand(Mouse& mouse, MouseState& mouseTower) noexcept;
	void AddItem(MenuItem* item, IObervable* obs);
	void AddItem(MenuItem* item);
	void ResetItem() noexcept;
	inline RectF GetRect() { return RectF(pos, width, height); }
	inline VecF GetPos() { return pos; }
	inline float GetWidth() { return width; }
	inline float GetHeight() { return height; }
private:
	VecF pos;
	float width;
	float height;
	Color color;
	std::vector<MenuItem*> items;
};