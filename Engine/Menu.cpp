#include "Menu.h"

void Menu::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim((VecI)pos, (int)width,(int)height , color);
	std::for_each(items.begin(), items.end(), [&gfx](auto& i) { i.second->Draw(gfx); });
}

void Menu::Update(float dt)
{
	std::for_each(items.begin(), items.end(), [&dt](auto& i) { i.second->Update(dt); });
}

void Menu::AddItem(std::shared_ptr<IGui> item)
{
	items.insert({ item->GetID(), item });
}

void Menu::OnNotify()
{
	
}
