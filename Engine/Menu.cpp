#include "Menu.h"

Menu::Menu(VecF pos, float width, float height, Color color)
	:
	pos(pos),
	width(width),
	height(height),
	color(color)
{}

void Menu::Draw(Graphics & gfx) const noexcept
{
	gfx.DrawRectDim((VecI)pos, (int)width, (int)height, color);
	for (auto i : items)
	{
		i->Draw(gfx);
	}
}

void Menu::Update(float dt, Mouse & mouse) noexcept
{
	for (auto i : items)
	{
		i->Update(dt, mouse);
	}
}

void Menu::MouseLeave() noexcept
{
	for (auto i : items)
	{
		i->MouseLeave();
	}
}

void Menu::ProcessCommand(Mouse & mouse, MouseState & mouseTower) noexcept
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
			mouseTower.typeDame = nullptr;
		}
	}
}

void Menu::AddItem(MenuItem * item, IObervable * obs)
{
	items.emplace_back(item);
	item->AddObs(obs);
}

void Menu::AddItem(MenuItem * item)
{
	items.emplace_back(item);
}

void Menu::ResetItem() noexcept
{
	for (auto i : items)
	{
		i->ResetState();
	}
}
