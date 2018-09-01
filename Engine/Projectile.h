#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
#include "TypeDame.h"
class Projectile : public PhysicObject
{
public:
	Projectile(b2World& box2DEngine, int curTarget, const b2Vec2& worldPos,float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f })
		:
		PhysicObject(box2DEngine, CollisionFillter::BOX, CollisionFillter::ENEMY,worldPos, false, false, size, linVel),
		targetID(curTarget)
	{
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx) const
	{
		const b2Vec2 pos = body->GetPosition();
		gfx.DrawRectDim(body->GetPosition(), size, Colors::Magenta);
	}
	void Update(float dt)
	{
		if (targetID != -1)
		{
			//b2Vec2 dir =  enemy->getBody().GetPosition() - body->GetPosition();
			//SetVelocity(dir);
		}
	}
private:
	int targetID = -1;
};