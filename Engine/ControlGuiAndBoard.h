#pragma once
#include "IMediator.h"
#include "Background.h"
#include "MenuManager.h"
#include "World.h"
#include "GameSettings.h"
class ControlGuiAndBoard : public IMediator
{
public:
	ControlGuiAndBoard(Background* bg, MenuManager* menuMgr, World* world)
		:
		bg(*bg),
		menuMgr(*menuMgr),
		world(*world)
	{
		this->bg.AddMediator(this);
		this->menuMgr.AddMediator(this);
		this->world.AddMediator(this);
	}
	/**********************************/
	/*  Control Gui and Background    */
	void OpenUpgradeMenu(int towerIndex) override
	{
		assert(towerIndex != -1);
		if (menuMgr.isUpgradeMenuOpen() && !world.IsTowerMaxLv(towerIndex))
		{
			towerIndexInWorld = towerIndex;
			menuMgr.ChangeUpgradeMenu();
		}
	}
	void UpgradeTower() override
	{
		world.UpgradeTower(mouseGame.getElement(), towerIndexInWorld);
		towerIndexInWorld = -1;
		mouseGame.Clear();
	}
	void ActiveWarningText(int newType) override
	{
		menuMgr.ActiveWarningText(newType);
	}
	void OnRightClickFromGUI() override
	{
		mouseGame.Clear();
		if (!menuMgr.isUpgradeMenuOpen())
		{
			menuMgr.ChangeMainMenu();
			towerIndexInWorld = -1;
		}
	}
	void MouseClickOnBackground(MouseState mouseState, const b2Vec2& mousePos, const b2Vec2& worldTilePos) override
	{
		switch (mouseState)
		{
		case None:
		{
			std::vector<Tower*> towerList = world.GetBodyList<Tower>(mousePos, mouseQuerySize);
			if (!towerList.empty())
			{
				OpenUpgradeMenu(towerList[0]->GetTowerIndex());
			}
			break;
		}
		case BuildTower:
		{
			std::vector<Tower*> towerList = world.GetBodyList<Tower>(mousePos, mouseQuerySize);
			if (towerList.empty())
			{
				world.MakeTower(mouseGame.getElement(), mouseGame.getElement()->getColor(), worldTilePos,5.0f);
			}
			break;
		}
		/*case SellTower:
		{
			auto bodyList = world.GetBodyList(worldTilePos, mouseQuerySize);
			break;
		}
		case SwapTower:
		{
			auto bodyList = world.GetBodyList(worldTilePos, mouseQuerySize);
			break;
		}
		case BuildEntity:
			break;*/
		}
	}
	/**********************************/


	/**********************************/
	/*      Control World Object      */
	void MakeTower(Element* element, Color c, const b2Vec2& worldPos, float size = 1.0f) override
	{
		world.MakeTower(element, c, worldPos, size);
	}
	int GetGold() const override
	{
		return world.GetGold();
	}
	bool CanAffordTower() const override
	{
		return world.CanAffordTower(GetMouseGame());
	}
	void DeleteTower(int towerIndex) override
	{
		world.SellTower(towerIndex);
	}
	/**********************************/
private:
	MenuManager& menuMgr;
	World& world;
	Background& bg;
	int towerIndexInWorld = -1;
	float mouseQuerySize = 0.1f;
};