#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
#include "Element.h"
#include "SharedAnimation.h"
#include "GameSettings.h"
#include "SoundEffect.h"
class Projectile : public PhysicObject
{
public:
	Projectile(b2World& box2DEngine, Element* element,int curTarget, const b2Vec2& worldPos,float size = 0.2f, float maxSpeedSq = 50.0f, const b2Vec2& linVel = { 0.0f,0.0f })
		:
		PhysicObject(box2DEngine, CollisionFillter::BULLET, CollisionFillter::ENEMY,worldPos, true, false, size, linVel),
		targetID(curTarget),
		size(size),
		projectileAnimation(element->GetProjectileAnimation()),
		element(element),
		maxSpeedSq(maxSpeedSq)
	{
		Codex<SoundEffect>::Retrieve(L"Data\\Sounds\\shot.sfx")->Play(0.1f);
		body->SetUserData(this);
	}

	void Draw(Graphics& gfx, const VecI& camPos) const
	{
		//gfx.DrawCircle(body->GetPosition(), size, Colors::Magenta);
		projectileAnimation.DrawOffset(gfx.ToScreenSpace(body->GetPosition()) + camPos, gfx);
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
	Element* getElement()
	{
		return element;
	}
	VecI GetExplosionPos()
	{
		return explosionPos;
	}
	void SetVelocity(const b2Vec2& dir)
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
	float GetDame()
	{
		return element->getDame();
	}
	void SetExplosionPos(const VecI& pos)
	{
		explosionPos = pos;
	}
	int GetElementType()
	{
		return element->getType();
	}
private:
	static constexpr float deadTimer = 3.0f;
	SharedAnimation projectileAnimation;
	Element* element;
	VecI explosionPos = { 0,0 };
	int targetID = -1;
	float maxSpeedSq;
	float timer = 0.0f;
	float size;
};