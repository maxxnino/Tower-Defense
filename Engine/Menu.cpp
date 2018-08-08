#include "Menu.h"

void Menu::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim((VecI)pos, (int)width,(int)height , color);
	for (auto i : items)
	{
		i->Draw(gfx);
	}
	//board.Draw(gfx);
}

void Menu::Update(float dt)
{
	for (auto i : items)
	{
		i->Update(dt);
	}
}

void Menu::ProccessCommand(Mouse & mouse)
{
	board.ProcessComand(mouse);
	//board.Update();
}

void Menu::AddItem(std::shared_ptr<IGui> item)
{
	items.emplace_back(item);
	board.Subcribe(item);
}

void Menu::OnNotify()
{
}
