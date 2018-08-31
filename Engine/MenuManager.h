#pragma once
#include "Menu.h"
#include "Button.h"
#include <algorithm>
#include <memory>
class MenuManager
{
public:
	MenuManager()
		:
		mainMenu({ 100.0f,500.0f }, 600.0f, 75.0f, Colors::Cyan),
		//mainMenuBtn01(VecF(100.0f + 100.0f , 500.0f + 7.0f), 60.0f, 60.0f),
		//mainMenuBtn02(VecF(100.0f + 100.0f + 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		//mainMenuBtn03(VecF(100.0f + 100.0f + 2.0f * 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		//deleteTowerBtn04(VecF(100.0f + 100.0f + 3.0f * 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		upgradeMenu({ 100.0f,500.0f }, 600.0f, 75.0f, Colors::MakeRGB(172u, 115u, 57u)),
		testMenu({ 100.0f,100.0f }, 600.0f, 75.0f, Colors::MakeRGB(100u, 30u, 100u)),
		//upgradeMenuBtn01(VecF(100.0f + 150.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		//upgradeMenuBtn02(VecF(100.0f + 150.0f + 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		//upgradeMenuBtn03(VecF(100.0f + 150.0f + 2.0f * 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		openMainMenu(VecF(100.0f + 100.0f, 100.0f + 7.0f), 60.0f, 60.0f),
		openUpgradeMenu(VecF(100.0f + 200.0f, 100.0f + 7.0f), 60.0f, 60.0f),
		openToggleMenu(VecF(100.0f + 300.0f, 100.0f + 7.0f), 60.0f, 60.0f)
	{
		activeMenu = &mainMenu;
		//main menu
		openMainMenu.getFunction() = [this]() {this->ChangeMainMenu(); };
		openMainMenu.setColor(Colors::Red);

		openUpgradeMenu.getFunction() = [this]() {this->ChangeUpgradeMenu(); };
		openUpgradeMenu.setColor(Colors::Green);

		openToggleMenu.getFunction() = [this]() {this->ToggleMenu(); };
		openToggleMenu.setColor(Colors::Blue);

		testMenu.AddItem(&openMainMenu);
		testMenu.AddItem(&openUpgradeMenu);
		testMenu.AddItem(&openToggleMenu);
		
		//upgrademenu

		
	}
	void Update(float dt, Mouse& mouse)
	{
		ProcessCommand(mouse);
		activeMenu->Update(dt, mouse);
		testMenu.Update(dt, mouse);
	}
	void Draw(Graphics& gfx)
	{
		activeMenu->Draw(gfx);
		testMenu.Draw(gfx);
	}

private:

	void ProcessCommand(Mouse& mouse)
	{
		if (activeMenu->GetRect().isContaint(mouse.GetPos()))
		{
			activeMenu->ProcessCommand(mouse);
		}
		else
		{
			activeMenu->MouseLeave();
		}
		if (testMenu.GetRect().isContaint(mouse.GetPos()))
		{
			testMenu.ProcessCommand(mouse);
		}
		else
		{
			testMenu.MouseLeave();
		}
	}
	void ChangeMainMenu()
	{
		activeMenu = &mainMenu;
	}
	void ChangeUpgradeMenu()
	{
		activeMenu = &upgradeMenu;
	}
	void ToggleMenu()
	{
		if (activeMenu == &mainMenu)
		{
			activeMenu = &upgradeMenu;
		}
		else
		{
			activeMenu = &mainMenu;
		}
	}
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
	Menu* activeMenu = nullptr;
	//Make main menu and button
	Menu mainMenu;
	//Button mainMenuBtn01;
	//Button mainMenuBtn02;
	//Button mainMenuBtn03;
	//Button deleteTowerBtn04;

	//Upgrade Menu
	Menu upgradeMenu;
	//Button upgradeMenuBtn01;
	//Button upgradeMenuBtn02;
	//Button upgradeMenuBtn03;

	//test button
	Menu testMenu;
	Button openMainMenu;
	Button openUpgradeMenu;
	Button openToggleMenu;
};