#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
#include "Element.h"
#include "Animation.h"
class Projectile : public PhysicObject
{
public:
	Projectile(b2World& box2DEngine, int curTarget, const b2Vec2& worldPos,float size = 0.2f,const b2Vec2& linVel = { 0.0f,0.0f })
		:
		PhysicObject(box2DEngine, CollisionFillter::BULLET, CollisionFillter::ENEMY,worldPos, true, false, size, linVel),
		targetID(curTarget),
		size(size),
		offSet(int(size  * 2.0f * Graphics::scalePixel), int(size  * 2.0f * Graphics::scalePixel)),
		projectileAnimation(0,0,30,30,2, Codex<Surface>::Retrieve(L"Images\\pm_pro_30_30_2.png"), 0.1f, Colors::Black)
	{
		body->SetUserData(this);
	}

	void Draw(Graphics& gfx) const
	{
		//gfx.DrawCircle(body->GetPosition(), size, Colors::Magenta);
		projectileAnimation.Draw(gfx.ToScreenSpace(body->GetPosition()) - offSet, gfx);
	}
	inline int GetEnemyID() noexcept
	{
		return targetID;
	}
	void Update(float dt)
	{
		projectileAnimation.Update(dt);
	}
	bool CooldownToDead(float dt) noexcept
	{
		timer += dt;
		if (timer >= deadTimer)
		{
			return true;
		}
		return false;
	}

	/**********************************/
	/*Virtual function for PhysiObject*/
	void SetVelocity(const b2Vec2& dir) override
	{
		b2Vec2 vel = body->GetLinearVelocity() + dir;
		const float curSpeedSq = std::pow(vel.x, 2) + std::pow(vel.y, 2);
		if (curSpeedSq > maxSpeedSq)
		{
			float factor = std::sqrt(maxSpeedSq / curSpeedSq);
			vel = factor * vel;
		}
		body->SetLinearVelocity(vel);
	}
	int GetDame() override
	{
		return dame;
	}
	/***********************************/
private:
	static constexpr float deadTimer = 3.0f;
	Animation projectileAnimation;
	VecI offSet;
	int dame = 2;
	int targetID = -1;
	float maxSpeedSq = 50.0f;
	float timer = 0.0f;
	float size;
};