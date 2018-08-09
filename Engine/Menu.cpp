#include "Menu.h"

void Menu::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim((VecI)pos, (int)width,(int)height , color);
	for (auto i : items)
	{
		i->Draw(gfx);
	}
}

void Menu::Update(float dt, Mouse& mouse)
{
	for (auto i : items)
	{
		i->Update(dt, mouse);
	}
}

void Menu::AddItem(std::shared_ptr<IGui> item)
{
	items.emplace_back(item);
}
