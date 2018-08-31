#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
#include "TypeDame.h"
#include "Enemy.h"
class Projectile : public PhysicObject
{
public:
	Projectile(b2World& box2DEngine, const b2Vec2& worldPos,float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f })
		:
		PhysicObject(box2DEngine, CollisionFillter::BOX, CollisionFillter::ENEMY,worldPos, false, false, size, linVel),
		enemy(enemy)
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
		if (enemy)
		{
			b2Vec2 dir =  enemy->getBody().GetPosition() - body->GetPosition();
			SetVelocity(dir);
		}
	}
	void AddEnemy(Enemy* enemy)
	{
		if (enemy)
		{
			this->enemy = enemy;
			b2Vec2 dir =  enemy->getBody().GetPosition() - body->GetPosition();
			SetVelocity(dir);
		}
	}
private:
	Enemy* enemy = nullptr;
};