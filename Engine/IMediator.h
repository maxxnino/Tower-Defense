#pragma once
#include "MouseGame.h"
class IMediator
{
public:
	virtual void OpenUpgradeMenu(int index) = 0;
	virtual void UpgradeTower() = 0;
	virtual MouseGame* GetMouseGame() = 0;
};