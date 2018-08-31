#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
class Enemy : public PhysicObject
{
public:
	Enemy(b2World& box2DEngine)
		:
		PhysicObject(box2DEngine, CollisionFillter::ENEMY, CollisionFillter::BASE | CollisionFillter::TOWER, { -20.0f,0.0f }, false, false, 1.0f, {2.0f,0.0f})
	{
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx)
	{
		gfx.DrawRectDim(body->GetPosition(), 1.0f, Colors::Magenta);
	}
	void MarkAsDead()
	{
		isDead = true;
		//Notify(this);
	}
	bool isRemove()
	{
		return isDead;
	}
private:
	bool isDead = false;
};