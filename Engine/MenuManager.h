#pragma once
#include "Menu.h"
#include "Button.h"
#include "Board.h"
#include "Observer.h"
#include <algorithm>
#include "MouseState.h"
#include "TypeDame.h"
#include "BuildableTile.h"
class MenuManager : public Observer, public IObervable
{
public:
	MenuManager()
		:
		mainMenu({ 100.0f,500.0f }, 600.0f, 75.0f, Colors::Cyan),
		mainMenuBtn01(VecF(100.0f + 150.0f , 500.0f + 7.0f), 60.0f, 60.0f),
		mainMenuBtn02(VecF(100.0f + 150.0f + 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		mainMenuBtn03(VecF(100.0f + 150.0f + 2.0f * 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		upgradeMenu({ 100.0f,500.0f }, 600.0f, 75.0f, Colors::Yellow),
		upgradeMenuBtn01(VecF(100.0f + 150.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		upgradeMenuBtn02(VecF(100.0f + 150.0f + 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		upgradeMenuBtn03(VecF(100.0f + 150.0f + 2.0f * 100.0f, 500.0f + 7.0f), 60.0f, 60.0f)
	{
		activeMenu = &mainMenu;
		//main menu
		mainMenuBtn01.setData(&(mouseTower.fire));
		mainMenuBtn02.setData(&(mouseTower.ice));
		mainMenuBtn03.setData(&(mouseTower.lighting));
		mainMenuBtn01.setColor(mouseTower.fire.getColor());
		mainMenuBtn02.setColor(mouseTower.ice.getColor());
		mainMenuBtn03.setColor(mouseTower.lighting.getColor());
		mainMenu.AddItem(&mainMenuBtn01, &mouseTower);
		mainMenu.AddItem(&mainMenuBtn02, &mouseTower);
		mainMenu.AddItem(&mainMenuBtn03, &mouseTower);
		
		//upgrademenu
		upgradeMenuBtn01.setData(&(mouseTower.fire));
		upgradeMenuBtn02.setData(&(mouseTower.ice));
		upgradeMenuBtn03.setData(&(mouseTower.lighting));
		upgradeMenuBtn01.setColor(mouseTower.fire.getColor());
		upgradeMenuBtn02.setColor(mouseTower.ice.getColor());
		upgradeMenuBtn03.setColor(mouseTower.lighting.getColor());
		upgradeMenu.AddItem(&upgradeMenuBtn01);
		upgradeMenu.AddItem(&upgradeMenuBtn02);
		upgradeMenu.AddItem(&upgradeMenuBtn03);
		
	}
	void Update(float dt, Mouse& mouse)
	{
		activeMenu->Update(dt, mouse);
	}
	void ProcessCommand(Mouse& mouse)
	{
		if (activeMenu->GetRect().isContaint(mouse.GetPos()))
		{
			activeMenu->ProcessCommand(mouse,mouseTower);
		}
		else
		{
			activeMenu->MouseLeave();
		}
	}
	void OnNotify(Observer* dataUser) override
	{
		if (activeMenu == &mainMenu)
		{
			auto obs = static_cast<BuildableTile*>(dataUser);
			activeMenu = &upgradeMenu;
			activeMenu->ResetItem();
			upgradeMenuBtn01.Clear();
			upgradeMenuBtn02.Clear();
			upgradeMenuBtn03.Clear();
			upgradeMenuBtn01.AddObs(obs);
			upgradeMenuBtn01.AddObs(this);
			upgradeMenuBtn02.AddObs(obs);
			upgradeMenuBtn02.AddObs(this);
			upgradeMenuBtn03.AddObs(obs);
			upgradeMenuBtn03.AddObs(this);
		}
		else
		{
			activeMenu = &mainMenu;
			activeMenu->ResetItem();
		}
	}
	void Draw(Graphics& gfx) const
	{
		activeMenu->Draw(gfx);
	}
	int getData()
	{
		
	}
	IObervable* GetMouseTowerObs()
	{
		return &mouseTower;
	}
private:
	/*void MakeMenu(VecF menuPos, float menuW, float menuH)
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
	}*/
private:
	MouseState mouseTower;
	Menu* activeMenu = nullptr;
	//Make main menu and button
	Menu mainMenu;
	Button mainMenuBtn01;
	Button mainMenuBtn02;
	Button mainMenuBtn03;

	//Upgrade Menu
	Menu upgradeMenu;
	Button upgradeMenuBtn01;
	Button upgradeMenuBtn02;
	Button upgradeMenuBtn03;
	
};