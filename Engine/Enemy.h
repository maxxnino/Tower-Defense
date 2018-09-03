#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
class Enemy : public PhysicObject
{
public:
	Enemy(b2World& box2DEngine, int id, float size)
		:
		PhysicObject(box2DEngine, CollisionFillter::ENEMY, CollisionFillter::BORDER |CollisionFillter::BULLET | CollisionFillter::BASE | CollisionFillter::TOWER,
			{ -20.0f,0.0f }, true, false, size, {6.0f,0.0f}),
		id(id),
		size(size)
	{
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx)
	{
		gfx.DrawCircle(body->GetPosition(), size, Colors::Yellow);
	}
	
	bool IsReachtBase() { return isReachBase; }
	int GetGold() { return gold; }
	/**********************************/
	/*Virtual function for PhysiObject*/
	int GetID() override { return id; }
	void ApplyDame(int dame) override
	{
		Hp -= dame;
		if (Hp <= 0)
		{
			isDestroyed = true;
		}
	}
	int GetDame() override { return dame; }
	void MarkReachBase() override { isReachBase = true; }
	/***********************************/
	
private:
	bool isReachBase = false;
	int Hp = 10;
	int gold = 1;
	int dame = 1;
	int id;
	float size;
};