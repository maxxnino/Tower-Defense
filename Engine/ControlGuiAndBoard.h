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
	void OpenUpgradeMenu(int towerIndex, int tileIndex) override
	{
		assert(towerIndex != -1);
		if (menuMgr.isUpgradeMenuOpen() && !world.IsTowerMaxLv(towerIndex))
		{
			towerIndexInWorld = towerIndex;
			trackingTile = tileIndex;
			menuMgr.ChangeUpgradeMenu();
		}
	}
	void UpgradeTower() override
	{
		world.UpgradeTower(mouseGame.getElement(), towerIndexInWorld);
		towerIndexInWorld = -1;
		trackingTile = -1;
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
			trackingTile = -1;
		}
	}
	void MouseClickOnBackground(MouseState mouseState, VecI worldPos) override
	{
		switch (mouseState)
		{
		case None:

			break;
		case BuildTower:
			break;
		case SellTower:
			break;
		case SwapTower:
			break;
		case BuildEntity:
			break;
		}
	}
	/**********************************/


	/**********************************/
	/*      Control World Object      */
	int MakeTower(Element* element, Color c, const b2Vec2& worldPos, float size = 1.0f) override
	{
		return world.MakeTower(element, c, worldPos, size);
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
	int trackingTile = -1;
};