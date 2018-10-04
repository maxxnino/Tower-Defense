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
	/**********************************/


	/**********************************/
	/*      Control World Object      */
	int MakeTower(const b2Vec2& worldPos) override
	{
		return world.MakeTower(mouseGame.getElement(), mouseGame.getElement()->getColor(), worldPos);
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