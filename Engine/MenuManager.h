#pragma once
#include "Menu.h"
#include "Button.h"
#include "Board.h"
#include "MouseCommand.h"
#include "MouseGame.h"
#include <algorithm>
class MenuManager
{
public:
	MenuManager(MouseCommand* newMc)
		:
		mc(newMc),
		brdGUI({ 0.0f,0.0f }, (float)Graphics::ScreenWidth, (float)Graphics::ScreenHeight)
	{
		//bottom menu
		{
			const VecF menuPos = { 100.0f,500.0f };
			MakeMenu(menuPos, 600.0f, 75.0f);
			AddVerticalButton(menuPos, 3, 70.0f, 7.0f, 100.0f, 60.0f, 60.0f);
		}
	}
	void Update(float dt, MouseGame& mouse)
	{
		brdGUI.ProcessComand(mouse);
		for (auto& m : menus)
		{
			m->Update(dt,mouse.getMouse());
		}
	}
	void Draw(Graphics& gfx) const
	{
		for (auto& m : menus)
		{
			m->Draw(gfx);
		}
	}
private:
	void MakeMenu(VecF menuPos, float menuW, float menuH)
	{
		auto menu = std::make_shared<Menu>(Menu(menuPos, menuW, menuH, Colors::Cyan));
		menus.emplace_back(menu);
		brdGUI.AddItem(menu);
	}
	void AddVerticalButton(VecI menuPos, int nBtn, float paddingLeft, float paddingTop, float spaceBetweenBtn, float btwWidth, float btnHeight)
	{
		for (int i = 0; i < nBtn; i++)
		{
			auto b = std::make_shared<Button>(menuPos + VecF(paddingLeft + (float)i * spaceBetweenBtn, paddingTop), btwWidth, btnHeight, Colors::Red);
			b->addDataButton(i + 1);
			b->addBtnListener(mc);
			menus.back()->AddItem(b);
			brdGUI.AddItem(b);
		}
	}
	void AddHorizontalButton(VecI menuPos, int nBtn, float paddingLeft, float paddingTop, float spaceBetweenBtn, float btwWidth, float btnHeight)
	{
		for (int i = 0; i < nBtn; i++)
		{
			auto b = std::make_shared<Button>(menuPos + VecF(paddingLeft, paddingTop + (float)i * spaceBetweenBtn), btwWidth, btnHeight, Colors::Red);
			menus.back()->AddItem(b);
			brdGUI.AddItem(b);
		}
	}
private:
	std::vector<std::shared_ptr<Menu>> menus;
	Board brdGUI;
	MouseCommand* mc;
};