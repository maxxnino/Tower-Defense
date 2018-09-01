#pragma once
#include "MouseGame.h"
class IMediator
{
public:
	//control gui and board object
	virtual void OpenUpgradeMenu(int towerIndex) = 0;
	virtual void UpgradeTower() = 0;
	MouseGame* GetMouseGame()
	{
		return &mouseGame;
	}

	//control world object
	virtual int MakeTower(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f) = 0;
protected:
	MouseGame mouseGame;
};