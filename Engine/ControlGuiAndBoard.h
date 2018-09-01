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
	//control gui and board object
	void OpenUpgradeMenu(int towerIndex, Color* towerColor) override
	{
		assert(towerIndex != -1);
		if (!world.IsTowerMaxLv(towerIndex))
		{
			towerIndexInWorld = towerIndex;
			colorBuildableTile = towerColor;
			menuMgr.ChangeUpgradeMenu();
		}
	}

	void UpgradeTower() override
	{
		*colorBuildableTile = world.UpgradeTower(mouseGame.getTypeDame(), towerIndexInWorld);
		ResetTrackingData();
		mouseGame.Clear();
	}

	//control world object
	std::pair<int, Color> MakeTower(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f) override
	{
		return std::move(world.MakeTower(typeDame, c, worldPos, size));
	}
	int MakeEnemy(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f }) override
	{
		return world.MakeEnemy(typeDame, c, worldPos, size, linVel);
	}
	int MakeBullet(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f }) override
	{
		return world.MakeBullet(typeDame, c, worldPos, size, linVel);
	}
private:
	void ResetTrackingData()
	{
		towerIndexInWorld = -1;
		colorBuildableTile = nullptr;
	}
private:
	MenuManager& menuMgr;
	World& world;
	BoardGame& board;
	int towerIndexInWorld = -1;
	Color* colorBuildableTile = nullptr;
};