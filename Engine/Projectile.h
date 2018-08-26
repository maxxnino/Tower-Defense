#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
#include "TypeDame.h"

class Projectile : public PhysicObject
{
public:
	Projectile(b2World& box2DEngine, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f })
		:
		PhysicObject(box2DEngine, CollisionFillter::BOX, CollisionFillter::ENEMY,worldPos, false, false, size, linVel)
	{
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx)
	{
		const b2Vec2 pos = body->GetPosition();
		gfx.DrawRectDim(body->GetPosition(), size, Colors::Magenta);
	}
private:
};