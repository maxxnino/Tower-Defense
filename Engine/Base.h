#pragma once
#include "PhysicObject.h"
#include "GameSettings.h"
class Base : public PhysicObject
{
public:
	Base(b2World& box2DEngine, const b2Vec2& worldPos, VecF size, bool isCircle = false)
		:
		PhysicObject(box2DEngine, CollisionFillter::BASE, CollisionFillter::ENEMY, worldPos, size.x, size.y, isCircle),
		size(size)
	{
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx) const
	{
		gfx.DrawRectDim(body->GetPosition(), size, Colors::Blue);
	}
	void ApplyDame(int type, float dame) override
	{
		Hp -= dame;
		if (Hp <= 0)
		{
			isDestroyed = true;
		}
	}
private:
	float Hp = GameSettings::Get().GetData("[Base Hp]");
	VecF size;
};