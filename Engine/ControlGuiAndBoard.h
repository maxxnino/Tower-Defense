#pragma once
#include "IMediator.h"
#include "BoardGame.h"
#include "MenuManager.h"
class ControlGuiAndBoard : public IMediator
{
public:
	ControlGuiAndBoard(BoardGame* board, MenuManager* menuMgr)
		:
		board(*board),
		menuMgr(*menuMgr)
	{
		this->board.AddMediator(this);
		this->menuMgr.AddMediator(this);
	}
	void OpenUpgradeMenu(int index) override
	{
		towerIndex = index;
		menuMgr.ChangeUpgradeMenu();
	}
	void UpgradeTower() override
	{
		board.tileAt(towerIndex).UpgradeTower(mouseGame.typeDame);
		mouseGame.typeDame = nullptr;
	}
	MouseGame* GetMouseGame() override
	{
		return &mouseGame;
	}
private:
	BoardGame& board;
	MenuManager& menuMgr;
	MouseGame mouseGame;
	int towerIndex = -1;
};