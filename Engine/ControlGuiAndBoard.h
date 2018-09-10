#pragma once
#include "IMediator.h"
#include "BoardGame.h"
#include "MenuManager.h"
#include "World.h"
class ControlGuiAndBoard : public IMediator
{
public:
	ControlGuiAndBoard(BoardGame* board, MenuManager* menuMgr, World* world)
		:
		board(*board),
		menuMgr(*menuMgr),
		world(*world)
	{
		this->board.AddMediator(this);
		this->menuMgr.AddMediator(this);
		this->world.AddMediator(this);
	}
	/**********************************/
	/*  Control Gui and Board Bbject  */
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
	void SellTower() override
	{
		world.SellTower(towerIndexInWorld);
		board.tileAt(trackingTile).RemoveTowerIndex();
		trackingTile = -1;
		towerIndexInWorld = -1;
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
	/**********************************/
private:
	MenuManager& menuMgr;
	World& world;
	BoardGame& board;
	int towerIndexInWorld = -1;
	int trackingTile = -1;
};