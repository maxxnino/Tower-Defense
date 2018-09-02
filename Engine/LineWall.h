#pragma once
#include "PhysicObject.h"
class LineWall : public PhysicObject
{
public:
	LineWall(b2World& box2DEngine, const b2Vec2& beginPos, const b2Vec2& endPos)
		:
		beginPos(beginPos),
		endPos(endPos),
		PhysicObject(box2DEngine, CollisionFillter::BORDER, CollisionFillter::ENEMY, beginPos, endPos)
	{
		body->SetUserData(this);
	}

	/**********************************/
	/*Virtual function for PhysiObject*/
	void RemoveEnemyID(int id) override {}
	void AddEnemyID(int id) override {}
	void MarkDead() override {}
	int GetID() override { return -1; }
	void SetVelocity(const b2Vec2& dir) override {}
	/***********************************/
private:
	b2Vec2 beginPos;
	b2Vec2 endPos;
};

class Border
{
public:
	Border(b2World& box2DEngine)
		:
		top(box2DEngine, { -20.0f, 3.0f}, {20.0f, 3.0f }),
		bottom(box2DEngine, { -20.0f, -3.0f }, { 20.0f, -3.0f })
	{}
private:
	LineWall top;
	LineWall bottom;
};