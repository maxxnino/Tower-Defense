#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
class Enemy : public PhysicObject
{
public:
	Enemy(b2World& box2DEngine, int id, float size)
		:
		PhysicObject(box2DEngine, CollisionFillter::ENEMY, CollisionFillter::BORDER |CollisionFillter::BULLET | CollisionFillter::BASE | CollisionFillter::TOWER,
			{ -20.0f,0.0f }, true, false, size, {8.0f,0.0f}),
		id(id),
		size(size)
	{
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx)
	{
		gfx.DrawCircle(body->GetPosition(), size, Colors::Yellow);
	}
	
	bool isRemove()
	{
		return isDead;
	}


	/**********************************/
	/*Virtual function for PhysiObject*/
	int GetID() override
	{
		return id;
	}
	void ApplyDame(int dame) override
	{
		Hp -= dame;
		if (Hp <= 0)
		{
			isDead = true;
		}
	}
	int GetDame() override
	{
		return dame;
	}
	void MarkDead() override
	{
		isDead = true;
	}
	/***********************************/
	
private:
	bool isDead = false;
	int Hp = 10;
	int dame = 1;
	int id;
	float size;
};