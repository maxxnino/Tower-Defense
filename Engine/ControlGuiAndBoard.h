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
	void OpenUpgradeMenu(int towerIndex) override
	{
		assert(towerIndex != -1);
		if (!world.IsTowerMaxLv(towerIndex))
		{
			towerIndexInWorld = towerIndex;
			menuMgr.ChangeUpgradeMenu();
		}
	}
	void UpgradeTower() override
	{
		world.UpgradeTower(mouseGame.getTypeDame(), towerIndexInWorld);
		towerIndexInWorld = -1;
		mouseGame.Clear();
	}
	/**********************************/


	/**********************************/
	/*      Control World Bbject      */
	int MakeTower(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f) override
	{
		return world.MakeTower(typeDame, c, worldPos, size);
	}
	/**********************************/
private:
	MenuManager& menuMgr;
	World& world;
	BoardGame& board;
	int towerIndexInWorld = -1;
};