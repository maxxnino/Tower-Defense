#pragma once
#include "MouseGame.h"
class IMediator
{
public:
	/**********************************/
	/*  Control Gui and Board Bbject  */
	virtual void OpenUpgradeMenu(int towerIndex) = 0;
	virtual void UpgradeTower() = 0;
	MouseGame* GetMouseGame()
	{
		return &mouseGame;
	}
	/**********************************/


	/**********************************/
	/*      Control World Bbject      */
	virtual int MakeTower(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f) = 0;
	/**********************************/
protected:
	MouseGame mouseGame;
};