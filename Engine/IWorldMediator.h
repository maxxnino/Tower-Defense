#pragma once
#include <set>
#include "Element.h"
class IWorldMediator
{
public:
	virtual int MakeTower(Element* element, Color c, const b2Vec2& worldPos, float size = 1.0f) = 0;
	virtual void MakeEnemy() = 0;
	virtual void MakeBullet(int curTarget, Element* element, Color c, const b2Vec2& worldPos) = 0;
	virtual bool IsTowerMaxLv(int towerIndex) = 0;
	virtual void UpgradeTower(Element* element, int towerIndex) = 0;
	virtual int GetTargetEnemy(std::set<int>& enemyIDs, const b2Vec2& towerPos) = 0;
};