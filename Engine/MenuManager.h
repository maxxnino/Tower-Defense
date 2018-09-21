#pragma once
#include <algorithm>
#include <memory>
#include "Menu.h"
#include "Button.h"
#include "IComponent.h"
#include "Font.h"
#include "Codex.h"
#include "Animation.h"
class MenuManager : public IComponent
{
public:
	MenuManager()
		:
		font(Codex<Surface>::Retrieve(L"Images\\GUI\\Fixedsys16x28.bmp")),
		surf(Codex<Surface>::Retrieve(L"Images\\GUI\\menu_02.png")),
		coinAnimation(0,0,40,40,25, Codex<Surface>::Retrieve(L"Images\\GUI\\pm_coin_40_40_25.png"), 0.04f, Colors::Black),
		mainMenu({ 100.0f,500.0f }, 600.0f, 75.0f, Codex<Surface>::Retrieve(L"Images\\GUI\\menu_01.png")),
		mainMenuBtn01(VecF(150.0f + 100.0f , 513.0f), 50.0f, 50.0f),
		mainMenuBtn02(VecF(150.0f + 100.0f + 100.0f, 513.0f), 50.0f, 50.0f),
		mainMenuBtn03(VecF(150.0f + 100.0f + 2.0f * 100.0f, 513.0f), 50.0f, 50.0f),
		
		upgradeMenu({ 100.0f,500.0f }, 600.0f, 75.0f, Codex<Surface>::Retrieve(L"Images\\GUI\\menu_01.png")),
		upgradeMenuBtn01(VecF(100.0f + 150.0f, 513.0f), 50.0f, 50.0f),
		upgradeMenuBtn02(VecF(100.0f + 150.0f + 100.0f, 513.0f), 50.0f, 50.0f),
		upgradeMenuBtn03(VecF(100.0f + 150.0f + 2.0f * 100.0f, 513.0f), 50.0f, 50.0f),
		deleteTowerBtn04(VecF(100.0f + 150.0f + 3.0f * 100.0f, 513.0f), 50.0f, 50.0f)
	{
		activeMenu = &mainMenu;
		//main menu
		mainMenuBtn01.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeToFire();
			mediator->GetMouseGame()->ChangeState(MouseState::BuildTower);
		});
		mainMenuBtn02.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeToIce();
			mediator->GetMouseGame()->ChangeState(MouseState::BuildTower);
		});
		mainMenuBtn03.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeToLighting();
			mediator->GetMouseGame()->ChangeState(MouseState::BuildTower);
		});
		deleteTowerBtn04.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeState(MouseState::DeleteTower);
		});
		mainMenuBtn01.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->GetMouseGame()->Clear(); });
		mainMenuBtn02.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->GetMouseGame()->Clear(); });
		mainMenuBtn03.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->GetMouseGame()->Clear(); });
		deleteTowerBtn04.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->OnRightClickFromGUI(); });

		mainMenu.AddItem(&mainMenuBtn01);
		mainMenu.AddItem(&mainMenuBtn02);
		mainMenu.AddItem(&mainMenuBtn03);
		mainMenu.AddItem(&deleteTowerBtn04);
		//mainMenu.AddItem(&deleteTowerBtn04);

		//upgrademenu
		upgradeMenuBtn01.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeToFire();
			mediator->UpgradeTower();
			ChangeMainMenu();
		});
		upgradeMenuBtn02.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeToIce();
			mediator->UpgradeTower();
			ChangeMainMenu();
		});
		upgradeMenuBtn03.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeToLighting();
			mediator->UpgradeTower();
			ChangeMainMenu();
		});
		upgradeMenuBtn01.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->OnRightClickFromGUI(); });
		upgradeMenuBtn02.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->OnRightClickFromGUI(); });
		upgradeMenuBtn03.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->OnRightClickFromGUI(); });
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
		mainMenuBtn01.SetSprite(mouseGame->GetFireSurface());

		mainMenuBtn02.setColor(mouseGame->GetIceColor());
		mainMenuBtn02.SetSprite(mouseGame->GetWaterSurface());

		mainMenuBtn03.setColor(mouseGame->GetLightingColor());
		mainMenuBtn03.SetSprite(mouseGame->GetNatureSurface());

		upgradeMenuBtn01.setColor(mouseGame->GetFireColor());
		upgradeMenuBtn01.SetSprite(mouseGame->GetFireSurface());

		upgradeMenuBtn02.setColor(mouseGame->GetIceColor());
		upgradeMenuBtn02.SetSprite(mouseGame->GetWaterSurface());

		upgradeMenuBtn03.setColor(mouseGame->GetLightingColor());
		upgradeMenuBtn03.SetSprite(mouseGame->GetNatureSurface());

		deleteTowerBtn04.setColor(Colors::White);
		deleteTowerBtn04.SetSprite(Codex<Surface>::Retrieve(L"Images\\GUI\\pm_delete_button_50_50.png"));
	}
	void Update(float dt, Mouse& mouse)
	{
		ProcessCommand(mouse);
		activeMenu->Update(dt, mouse);
		coinAnimation.Update(dt);
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
		gfx.DrawSprite(0, 0, *surf, SpriteEffect::Copy{});
		coinAnimation.DrawAlpha({ 10,5 }, gfx);
		font.DrawText(std::to_string(mediator->GetGold()), {60,10},Colors::Green,gfx);
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
	bool isUpgradeMenuOpen()
	{
		return activeMenu != &upgradeMenu;
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
					mediator->OnRightClickFromGUI();
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
	const std::shared_ptr<Surface> surf;
	Animation coinAnimation;
	Menu* activeMenu = nullptr;
	IMediator* mediator = nullptr;
	bool isWarning = false;
	//0 draw
	int type = 0;
	std::string warningGoldText = "Yo!!! You poor as fuck !!!";
	std::string warningCantBuildText = "This tile already have a tower bitch !!!";
	float timer = 0.0f;
	//Make main menu and button
	Menu mainMenu;
	Button mainMenuBtn01;
	Button mainMenuBtn02;
	Button mainMenuBtn03;
	Button deleteTowerBtn04;

	//Upgrade Menu
	Menu upgradeMenu;
	Button upgradeMenuBtn01;
	Button upgradeMenuBtn02;
	Button upgradeMenuBtn03;
};