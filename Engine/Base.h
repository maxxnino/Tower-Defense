#pragma once
#include "PhysicObject.h"
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
	inline bool isGameOver() noexcept
	{
		return isDead;
	}
	void ApplyDame(int dame) override
	{
		Hp -= dame;
		if (Hp <= 0)
		{
			isDead = true;
		}
	}
private:
	int Hp = 10;
	bool isDead = false;
	VecF size;
};