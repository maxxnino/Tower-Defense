#pragma once
#include "Box.h"
#include "Graphics.h"
enum CollisionFillter {
	BOX = 0x0001,
	ENEMY = 0x0002
};
class Projectile : public Box
{
public:
	Projectile(b2World& box2DEngine, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f })
		:
		Box(box2DEngine, CollisionFillter::BOX, CollisionFillter::ENEMY, worldPos, size, linVel)
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