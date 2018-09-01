#pragma once
#include "TypeDame.h"
class IWorldMediator
{
public:
	virtual std::pair<int, Color> MakeTower(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f) = 0;
	virtual int MakeEnemy(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f }) = 0;
	virtual int MakeBullet(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f }) = 0;
	virtual bool IsTowerMaxLv(int towerIndex) = 0;
	virtual Color UpgradeTower(TypeDame* typeDame, int towerIndex) = 0;
};