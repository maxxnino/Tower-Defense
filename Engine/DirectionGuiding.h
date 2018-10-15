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
		PhysicObject(box2DEngine, CollisionFillter::GUIDING, CollisionFillter::ENEMY, worldPos, radian, radian, true,true)
	{
		body->SetUserData(this);
	}
	void Guiding(Enemy* enemy)
	{
		enemy->SetDir(dir);
	}
	void DrawDebug(Graphics& gfx, const Camera& cam) const
	{
		gfx.DrawCircle(cam.GetDrawPosition(worldPos), int(radian * Camera::scalePixel), c);
	}
	void OnClick()
	{
		c = Colors::Yellow;
	}
	void OnRelease()
	{
		c = Colors::Magenta;
	}
private:
	const b2Vec2 worldPos;
	const b2Vec2 dir;
	const float radian;
	Color c = Colors::Magenta;
};

class GuidingManager
{
public:
	GuidingManager(b2World& box2DEngine)
	{
		guiMgr.emplace_back(std::make_unique<DirectionGuiding>(box2DEngine, b2Vec2( 16.0f,9.0f ), 1.0f, b2Vec2( 0.0f,-1.0f )));
	}
	void DrawDebug(Graphics& gfx, const Camera& cam) const
	{
		for (const auto& g : guiMgr)
		{
			g->DrawDebug(gfx, cam);
		}
	}
	void MakeDirectionGuiding(b2World& box2DEngine, const b2Vec2& worldPos)
	{
		guiMgr.emplace_back(std::make_unique<DirectionGuiding>(box2DEngine, worldPos, 1.0f, b2Vec2(0.0f, -1.0f)));
	}
private:
	std::vector<std::unique_ptr<DirectionGuiding>> guiMgr;
};