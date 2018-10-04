#pragma once
#include "PhysicObject.h"
#include "GameSettings.h"
class Base : public PhysicObject
{
public:
	Base(b2World& box2DEngine, const b2Vec2& worldPos, float width, float height, bool isCircle = false)
		:
		PhysicObject(box2DEngine, CollisionFillter::BASE, CollisionFillter::ENEMY, worldPos, width, height, isCircle,true),
		width(width),
		height(height)
	{
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx, const Camera& cam) const
	{
		const auto drawPos = cam.GetDrawPosition(body->GetPosition());
		gfx.DrawRectDim(drawPos, (int)width * Camera::scalePixel,(int)height * Camera::scalePixel, Colors::Blue);
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
	float width;
	float height;
};