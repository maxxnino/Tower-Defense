#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
class Enemy : public PhysicObject
{
public:
	Enemy(b2World& box2DEngine, int id)
		:
		PhysicObject(box2DEngine, CollisionFillter::ENEMY, CollisionFillter::BULLET | CollisionFillter::BASE | CollisionFillter::TOWER, { -20.0f,0.0f }, false, false, 1.0f, {2.0f,0.0f}),
		id(id)
	{
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx)
	{
		gfx.DrawRectDim(body->GetPosition(), 1.0f, Colors::Magenta);
	}
	void RemoveEnemyID(int id) override {}
	void AddEnemyID(int id) override {}
	void MarkDead() override
	{
		isDead = true;
		//Notify(this);
	}
	int GetID() override
	{
		return id;
	}
	bool isRemove()
	{
		return isDead;
	}
private:
	bool isDead = false;
	int id;
};