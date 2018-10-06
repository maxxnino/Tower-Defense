#pragma once
#include <algorithm>
#include <memory>
#include "Menu.h"
#include "Button.h"
#include "IComponent.h"
#include "Font.h"
#include "Codex.h"
#include "Animation.h"
#include "ListenerBox2DGUI.h"
#include "MouseGui.h"
class MenuManager : public IComponent
{
public:
	MenuManager()
		:
		box2DGUI(std::make_unique<b2World>(b2Vec2(0.0f, 0.0f))),
		mouseGui(*box2DGUI),
		font(Codex<Surface>::Retrieve(L"Images\\GUI\\Fixedsys16x28.bmp")),
		surf(Codex<Surface>::Retrieve(L"Images\\GUI\\menu_02.png")),
		coinAnimation(0,0,40,40,25, Codex<Surface>::Retrieve(L"Images\\GUI\\pm_coin_40_40_25.png"), 0.04f, Colors::Black),
		mainMenu(*box2DGUI, { 0.0f, -12.0f }, 30.0f, 3.5f, Codex<Surface>::Retrieve(L"Images\\GUI\\menu_01.png")),
		mainMenuBtn01(*box2DGUI, {  -10.0f , -12.0f }, 2.5f, 2.5f),
		mainMenuBtn02(*box2DGUI, { -10.0f + 5.0f, -12.0f }, 2.5f, 2.5f),
		mainMenuBtn03(*box2DGUI, { -10.0f + 10.0f, -12.0f }, 2.5f, 2.5f),
		deleteTowerBtn04(*box2DGUI, { -10.0f + 15.0f, -12.0f }, 2.5f, 2.5f),
		swapTowerBtn05(*box2DGUI, { -10.0f + 20.0f, -12.0f }, 2.5f, 2.5f),
		upgradeMenu(*box2DGUI, { 0.0f, -12.0f }, 30.0f, 3.5f, Codex<Surface>::Retrieve(L"Images\\GUI\\menu_01.png")),
		upgradeMenuBtn01(*box2DGUI, { -10.0f , -12.0f }, 2.5f, 2.5f),
		upgradeMenuBtn02(*box2DGUI, { -10.0f + 10.0f, -12.0f }, 2.5f, 2.5f),
		upgradeMenuBtn03(*box2DGUI, { -10.0f + 20.0f, -12.0f }, 2.5f, 2.5f)
		
	{
		box2DGUI->SetContactListener(&listenerGUI);
		activeMenu = &mainMenu;
		//main menu
		mainMenuBtn01.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeToFire();
			mainMenuBtn01.Disable(1.0f);
		});
		mainMenuBtn02.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeToIce();
			mainMenuBtn02.Disable(1.0f);
		});
		mainMenuBtn03.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			mediator->GetMouseGame()->ChangeToLighting();
			mainMenuBtn03.Disable(1.0f);
		});
		deleteTowerBtn04.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			swapTowerBtn05.Disable(1.0f);
			mainMenu.DisableButton();
			mediator->GetMouseGame()->ChangeState(MouseState::SellTower);
		});
		swapTowerBtn05.AddEventListener(Mouse::Event::Type::LPress, [this]() {
			swapTowerBtn05.Disable(1.0f);
			mainMenu.DisableButton();
			mediator->GetMouseGame()->ChangeState(MouseState::SwapTower);
		});
		mainMenuBtn01.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->GetMouseGame()->Clear(); });
		mainMenuBtn02.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->GetMouseGame()->Clear(); });
		mainMenuBtn03.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->GetMouseGame()->Clear(); });
		deleteTowerBtn04.AddEventListener(Mouse::Event::Type::RPress, [this]() {mediator->OnRightClickFromGUI(); });

		mainMenu.AddButton(&mainMenuBtn01);
		mainMenu.AddButton(&mainMenuBtn02);
		mainMenu.AddButton(&mainMenuBtn03);
		mainMenu.AddButton(&deleteTowerBtn04);
		mainMenu.AddButton(&swapTowerBtn05);

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

		upgradeMenu.AddButton(&upgradeMenuBtn01);
		upgradeMenu.AddButton(&upgradeMenuBtn02);
		upgradeMenu.AddButton(&upgradeMenuBtn03);
		upgradeMenu.RemoveCollision();
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
		swapTowerBtn05.SetSprite(Codex<Surface>::Retrieve(L"Images\\GUI\\pm_swap_button_50_50.png"));
	}
	void Update(float dt, Mouse& mouse)
	{
		mouseGui.Update(dt, mouse);
		box2DGUI->Step(dt, velocityIterations, positionIterations);
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
		mouseGui.Draw(gfx);
		gfx.DrawSprite(0, 0, *surf, SpriteEffect::Copy{});
		coinAnimation.DrawAlpha({ 10,5 }, gfx);
		font.DrawText(std::to_string(mediator->GetGold()), {60,10},Colors::Green,gfx);
		DrawWaringText(gfx);
	}
	void ChangeMainMenu()
	{
		if (activeMenu != &mainMenu)
		{
			upgradeMenu.RemoveCollision();
			mainMenu.EnableCollision();
			activeMenu = &mainMenu;
		}
	}
	bool isUpgradeMenuOpen()
	{
		return activeMenu == &upgradeMenu;
	}
	void ChangeUpgradeMenu()
	{
		if (activeMenu != &upgradeMenu)
		{
			mainMenu.RemoveCollision();
			upgradeMenu.EnableCollision();
			activeMenu = &upgradeMenu;
		}
	}
	void EnableButton()
	{
		assert(activeMenu == &mainMenu);
		mainMenu.EnableButoon();
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
				font.DrawText(warningCantBuildText, { 80,50 }, Colors::Green, gfx);
				break;
			case 2:
				font.DrawText(warningCantSwapTower, { 80,50 }, Colors::Blue, gfx);
			default:
				break;
			}
		}
	}
	void ProcessCommand(Mouse& mouse)
	{
		/*if (activeMenu->GetRect().isContaint(mouse.GetPos()))
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
		}*/
	}
private:
	static constexpr int32 velocityIterations = 1;
	static constexpr int32 positionIterations = 1;
	std::unique_ptr<b2World> box2DGUI;
	ListenerBox2DGUI listenerGUI;
	MouseGui mouseGui;
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
	std::string warningCantSwapTower = "You can't see ? There is no tower to swap";
	float timer = 0.0f;
	//Make main menu and button
	Menu mainMenu;
	Button mainMenuBtn01;
	Button mainMenuBtn02;
	Button mainMenuBtn03;
	Button deleteTowerBtn04;
	Button swapTowerBtn05;
	//Upgrade Menu
	Menu upgradeMenu;
	Button upgradeMenuBtn01;
	Button upgradeMenuBtn02;
	Button upgradeMenuBtn03;
};