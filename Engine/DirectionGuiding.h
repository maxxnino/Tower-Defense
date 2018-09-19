#pragma once
#include "PhysicObject.h"
#include "Enemy.h"
#include "Graphics.h"
class DirectionGuiding : public PhysicObject
{
public:
	DirectionGuiding(b2World& box2DEngine, const b2Vec2& worldPos, float radian, const b2Vec2& dir)
		:
		worldPos(worldPos),
		dir(dir),
		radian(radian),
		PhysicObject(box2DEngine, CollisionFillter::GUIDING, CollisionFillter::ENEMY, worldPos, radian, radian, true)
	{
		body->SetUserData(this);
	}
	void Guiding(Enemy* enemy)
	{
		enemy->SetDir(dir);
	}
	void DrawDebug(Graphics& gfx)
	{
		gfx.DrawCircle(worldPos, radian, Colors::Magenta);
	}
private:
	const b2Vec2 worldPos;
	const b2Vec2 dir;
	const float radian;
};

class GuidingManager
{
public:
	GuidingManager(b2World& box2DEngine)
		:
		guiding01(box2DEngine, {16.0f,9.0f}, 1.0f, { 0.0f,-1.0f })
	{}
	void DrawDebug(Graphics& gfx)
	{
		guiding01.DrawDebug(gfx);
	}
private:
	DirectionGuiding guiding01;
};