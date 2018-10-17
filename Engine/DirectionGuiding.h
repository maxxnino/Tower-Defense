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
		mousePos(worldPos),
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
		const VecI drawPos = cam.GetDrawPosition(worldPos);
		gfx.DrawCircle(drawPos, int(radian * Camera::scalePixel), c);
		if (isSelected)
		{
			gfx.DrawLine(drawPos, cam.GetDrawPosition(mousePos), Colors::Blue);
		}
		else
		{
			gfx.DrawLine(drawPos, cam.GetDrawPosition(worldPos + 2.0f * dir), Colors::Blue);
		}
	}
	void OnClick()
	{
		c = Colors::Yellow;
		isSelected = true;
	}
	void OnRelease()
	{
		c = Colors::Magenta;
		isSelected = false;
	}
	bool SetDirection(const b2Vec2& newPos)
	{
		if (worldPos != newPos)
		{
			dir = newPos - worldPos;
			dir.Normalize();
			return true;
		}
		return false;
	}
	void SetMousePos(const b2Vec2& newPos)
	{
		mousePos = newPos;
	}
private:
	b2Vec2 worldPos;
	b2Vec2 dir;
	b2Vec2 mousePos;
	const float radian;
	Color c = Colors::Magenta;
	bool isSelected = false;
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
	void DeleteDeadBody()
	{
		for (size_t i = 0; i < guiMgr.size();)
		{
			if (guiMgr[i]->isRemove())
			{
				std::swap(guiMgr[i], guiMgr.back());
				guiMgr.pop_back();
			}
			else
			{
				i++;
			}
		}
	}
private:
	std::vector<std::unique_ptr<DirectionGuiding>> guiMgr;
};