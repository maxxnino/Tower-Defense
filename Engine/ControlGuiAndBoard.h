#pragma once
#include "IMediator.h"
#include "BoardGame.h"
#include "MenuManager.h"
#include "MouseGame.h"
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
		menuMgr.ChangeUpgradeMenu(index);
	}
	void UpgradeTower(int index) override
	{
		board.tileAt(index).UpgradeTower(mouseGame.typeDame);
	}
	void ChangeToFire() override
	{
		mouseGame.typeDame = &mouseGame.fire;
	}
	void ChangeToIce() override
	{
		mouseGame.typeDame = &mouseGame.ice;
	}
	void ChangeToLighting() override
	{
		mouseGame.typeDame = &mouseGame.lighting;
	}
private:
	BoardGame& board;
	MenuManager& menuMgr;
	MouseGame mouseGame;
};