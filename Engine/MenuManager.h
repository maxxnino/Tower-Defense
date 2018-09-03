#pragma once
#include <algorithm>
#include <memory>
#include "Menu.h"
#include "Button.h"
#include "IComponent.h"
#include "Font.h"
#include "Codex.h"
class MenuManager : public IComponent
{
public:
	MenuManager()
		:
		font(Codex<Surface>::Retrieve(L"Images\\Fixedsys16x28.bmp")),
		mainMenu({ 100.0f,500.0f }, 600.0f, 75.0f, Colors::Cyan),
		mainMenuBtn01(VecF(100.0f + 100.0f , 500.0f + 7.0f), 60.0f, 60.0f),
		mainMenuBtn02(VecF(100.0f + 100.0f + 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		mainMenuBtn03(VecF(100.0f + 100.0f + 2.0f * 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		//deleteTowerBtn04(VecF(100.0f + 100.0f + 3.0f * 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		upgradeMenu({ 100.0f,500.0f }, 600.0f, 75.0f, Colors::MakeRGB(172u, 115u, 57u)),
		upgradeMenuBtn01(VecF(100.0f + 150.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		upgradeMenuBtn02(VecF(100.0f + 150.0f + 100.0f, 500.0f + 7.0f), 60.0f, 60.0f),
		upgradeMenuBtn03(VecF(100.0f + 150.0f + 2.0f * 100.0f, 500.0f + 7.0f), 60.0f, 60.0f)
	{
		activeMenu = &mainMenu;
		//main menu
		mainMenuBtn01.GetLeftClickFunc() = [this]() {
			auto mouseGame = mediator->GetMouseGame();
			mouseGame->ChangeToFire();
		};
		mainMenuBtn02.GetLeftClickFunc() = [this]() {
			auto mouseGame = mediator->GetMouseGame();
			mouseGame->ChangeToIce();
		};
		mainMenuBtn03.GetLeftClickFunc() = [this]() {
			auto mouseGame = mediator->GetMouseGame();
			mouseGame->ChangeToLighting();
		};
		mainMenuBtn01.GetRightClickFunc() = [this]() {mediator->GetMouseGame()->Clear(); };
		mainMenuBtn02.GetRightClickFunc() = [this]() {mediator->GetMouseGame()->Clear(); };
		mainMenuBtn03.GetRightClickFunc() = [this]() {mediator->GetMouseGame()->Clear(); };
		mainMenu.AddItem(&mainMenuBtn01);
		mainMenu.AddItem(&mainMenuBtn02);
		mainMenu.AddItem(&mainMenuBtn03);

		//upgrademenu
		upgradeMenuBtn01.GetLeftClickFunc() = [this]() {
			auto mouseGame = mediator->GetMouseGame();
			mouseGame->ChangeToFire();
			mediator->UpgradeTower();
			ChangeMainMenu();
		};
		upgradeMenuBtn02.GetLeftClickFunc() = [this]() {
			auto mouseGame = mediator->GetMouseGame();
			mouseGame->ChangeToIce();
			mediator->UpgradeTower();
			ChangeMainMenu();
		};
		upgradeMenuBtn03.GetLeftClickFunc() = [this]() {
			auto mouseGame = mediator->GetMouseGame();
			mouseGame->ChangeToLighting();
			mediator->UpgradeTower();
			ChangeMainMenu();
		};
		upgradeMenuBtn01.GetRightClickFunc() = [this]() {mediator->GetMouseGame()->Clear(); };
		upgradeMenuBtn02.GetRightClickFunc() = [this]() {mediator->GetMouseGame()->Clear(); };
		upgradeMenuBtn03.GetRightClickFunc() = [this]() {mediator->GetMouseGame()->Clear(); };
		upgradeMenu.AddItem(&upgradeMenuBtn01);
		upgradeMenu.AddItem(&upgradeMenuBtn02);
		upgradeMenu.AddItem(&upgradeMenuBtn03);
	}

	// Remember update color for button after add mediator
	void AddMediator(IMediator* mediator) override
	{
		this->mediator = mediator;
		auto mouseGame = this->mediator->GetMouseGame();
		mainMenuBtn01.setColor(mouseGame->GetFireColor());
		mainMenuBtn02.setColor(mouseGame->GetIceColor());
		mainMenuBtn03.setColor(mouseGame->GetLightingColor());
		upgradeMenuBtn01.setColor(mouseGame->GetFireColor());
		upgradeMenuBtn02.setColor(mouseGame->GetIceColor());
		upgradeMenuBtn03.setColor(mouseGame->GetLightingColor());
	}
	void Update(float dt, Mouse& mouse)
	{
		ProcessCommand(mouse);
		activeMenu->Update(dt, mouse);
		if (isWarning)
		{
			timer += dt;
			if (timer >= 3.0f)
			{
				isWarning = false;
			}
		}
	}
	void Draw(Graphics& gfx)
	{
		activeMenu->Draw(gfx);
		font.DrawText(std::to_string(mediator->GetGold()), {10,10},Colors::Green,gfx);
		DrawWaringText(gfx);
	}
	void ChangeMainMenu()
	{
		if (activeMenu != &mainMenu)
		{
			activeMenu = &mainMenu;
			upgradeMenu.ResetItem();
		}
	}
	void ChangeUpgradeMenu()
	{
		if (activeMenu != &upgradeMenu)
		{
			activeMenu = &upgradeMenu;
			mainMenu.ResetItem();
		}
	}
	void ActiveWarningText(int newType)
	{
		isWarning = true;
		type = newType;
		timer = 0.0f;
	}
private:
	void DrawWaringText(Graphics& gfx) const
	{
		if (isWarning)
		{
			switch (type)
			{
			case 0:
				font.DrawText(warningGoldText, { 150,50 }, Colors::Red, gfx);
				break;
			case 1:
				font.DrawText(warningCantBuildText, { 80,50 }, Colors::Red, gfx);
				break;
			default:
				break;
			}
		}
	}
	void ProcessCommand(Mouse& mouse)
	{
		if (activeMenu->GetRect().isContaint(mouse.GetPos()))
		{
			activeMenu->ProcessCommand(mouse);
			while (!mouse.IsEmpty())
			{
				auto e = mouse.Read().GetType();
				if (e == Mouse::Event::Type::RPress)
				{
					mediator->GetMouseGame()->Clear();
				}
			}
		}
		else
		{
			activeMenu->MouseLeave();
		}
	}
private:
	Font font;
	Menu* activeMenu = nullptr;
	IMediator* mediator = nullptr;
	bool isWarning = false;
	int type = 0;
	std::string warningGoldText = "Yo!!! You poor as fuck !!!";
	std::string warningCantBuildText = "This tile already have a tower bitch !!!";
	float timer = 0.0f;
	//Make main menu and button
	Menu mainMenu;
	Button mainMenuBtn01;
	Button mainMenuBtn02;
	Button mainMenuBtn03;
	//Button deleteTowerBtn04;

	//Upgrade Menu
	Menu upgradeMenu;
	Button upgradeMenuBtn01;
	Button upgradeMenuBtn02;
	Button upgradeMenuBtn03;
};

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