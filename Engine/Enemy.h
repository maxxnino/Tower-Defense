#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
class Enemy : public PhysicObject
{
public:
	Enemy(b2World& box2DEngine, int id)
		:
		PhysicObject(box2DEngine, CollisionFillter::ENEMY, CollisionFillter::ENEMY | CollisionFillter::BORDER |CollisionFillter::BULLET | CollisionFillter::BASE | CollisionFillter::TOWER,
			{ -20.0f,0.0f }, true, false, 1.0f, {2.0f,0.0f}),
		id(id)
	{
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx)
	{
		gfx.DrawCircle(body->GetPosition(), 1.0f, Colors::Yellow);
	}
	
	bool isRemove()
	{
		return isDead;
	}


	/**********************************/
	/*Virtual function for PhysiObject*/
	void MarkDead() override
	{
		isDead = true;
	}
	int GetID() override
	{
		return id;
	}
	/***********************************/
	
private:
	bool isDead = false;
	int id;
	float size;
};