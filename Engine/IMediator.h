#pragma once
#include "MouseGame.h"
class IMediator
{
public:
	//control gui and board object
	virtual void OpenUpgradeMenu(int towerIndex, Color* towerColor) = 0;
	virtual void UpgradeTower() = 0;
	MouseGame* GetMouseGame()
	{
		return &mouseGame;
	}

	//control world object
	virtual std::pair<int, Color> MakeTower(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f) = 0;
	virtual int MakeBullet(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f }) = 0;
protected:
	MouseGame mouseGame;
};