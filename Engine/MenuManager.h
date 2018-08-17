#pragma once
#include "Menu.h"
#include "Button.h"
#include "Board.h"
#include "Listener.h"
#include <algorithm>
class MenuManager
{
public:
	MenuManager(ButtonListener* btnListener)
		:
		btnListener(btnListener)
	{
		//bottom menu
		{
			const VecF menuPos = { 100.0f,500.0f };
			MakeMenu(menuPos, 600.0f, 75.0f);
			AddVerticalButton(menuPos, 3, 150.0f, 7.0f, 100.0f, 60.0f, 60.0f);
		}
	}
	void Update(float dt, Mouse& mouse)
	{
		for (auto& m : menus)
		{
			m->Update(dt,mouse);
		}
	}
	void ProcessCommand(Mouse& mouse)
	{
		for (auto m : menus)
		{
			if (m->GetRect().isContaint(mouse.GetPos()))
			{
				m->ProcessCommand(mouse);
			}
			else
			{
				m->MouseLeave();
			}
		}
	}
	void Draw(Graphics& gfx) const
	{
		for (auto& m : menus)
		{
			m->Draw(gfx);
		}
	}
	int getData()
	{
		return btnListener->getData();
	}
private:
	void MakeMenu(VecF menuPos, float menuW, float menuH)
	{
		auto menu = std::make_shared<Menu>(Menu(menuPos, menuW, menuH, Colors::Cyan));
		menus.emplace_back(menu);
	}
	void AddVerticalButton(VecI menuPos, int nBtn, float paddingLeft, float paddingTop, float spaceBetweenBtn, float btwWidth, float btnHeight)
	{
		for (int i = 0; i < nBtn; i++)
		{
			auto b = std::make_shared<Button>(menuPos + VecF(paddingLeft + (float)i * spaceBetweenBtn, paddingTop), btwWidth, btnHeight, Colors::Red);
			b->setData(i + 1);
			b->addListener(btnListener);
			menus.back()->AddItem(b);
		}
	}
	void AddHorizontalButton(VecI menuPos, int nBtn, float paddingLeft, float paddingTop, float spaceBetweenBtn, float btwWidth, float btnHeight)
	{
		for (int i = 0; i < nBtn; i++)
		{
			auto b = std::make_shared<Button>(menuPos + VecF(paddingLeft, paddingTop + (float)i * spaceBetweenBtn), btwWidth, btnHeight, Colors::Red);
			menus.back()->AddItem(b);
		}
	}
private:
	std::vector<std::shared_ptr<Menu>> menus;
	ButtonListener* btnListener;
};