#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
#include "Codex.h"
class Enemy : public PhysicObject
{
public:
	Enemy(b2World& box2DEngine, int id, float size)
		:
		PhysicObject(box2DEngine, CollisionFillter::ENEMY, CollisionFillter::BORDER |CollisionFillter::BULLET | CollisionFillter::BASE | CollisionFillter::TOWER,
			{ -20.0f,0.0f }, true, false, size, {6.0f,0.0f}),
		id(id),
		size(size),
		offSet(int(size * Graphics::scalePixel))
	{
		if ((id % 3) == 0)
		{
			surf = Codex<Surface>::Retrieve(L"Images\\pm_enemy_03.png");
		}
		else if ((id % 2) == 0)
		{
			surf = Codex<Surface>::Retrieve(L"Images\\pm_enemy_02.png");
		}
		else
		{
			surf = Codex<Surface>::Retrieve(L"Images\\pm_enemy_01.png");
		}
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx)
	{
		const VecI pos = gfx.ToScreenSpace(body->GetPosition());
		
		if (isGetHit)
		{
			gfx.DrawSprite(pos.x - offSet, pos.y - offSet, *surf, SpriteEffect::Substitution{ Colors::Black,Colors::Red });
		}
		else
		{
			gfx.DrawSprite(pos.x - offSet, pos.y - offSet, *surf, SpriteEffect::AlphaBlendBaked{});
		}
	}
	
	bool IsReachtBase() { return isReachBase; }
	int GetGold() { return gold; }
	void Update(float dt)
	{
		const b2Vec2 vel = body->GetLinearVelocity();
		const float velChange = 6 - vel.x;
		const float impulse = body->GetMass() * velChange * dt; //disregard time factor
		body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(),true);
		if (isGetHit)
		{
			timerGetHit += dt;
			if (timerGetHit >= 0.03f)
			{
				timerGetHit = 0.0f;
				isGetHit = false;
			}
		}
	}
	/**********************************/
	/*Virtual function for PhysiObject*/
	int GetID() override { return id; }
	void ApplyDame(int dame) override
	{
		Hp -= dame;
		isGetHit = true;
		if (Hp <= 0)
		{
			isDestroyed = true;
		}
	}
	int GetDame() override { return dame; }
	void MarkReachBase() override { isReachBase = true; }
	/***********************************/
	
private:
	bool isReachBase = false;
	bool isGetHit = false;
	float timerGetHit = 0.0f;
	b2Vec2 speed = {6.0f,0.0f};
	const Surface* surf;
	int offSet;
	int Hp = 10;
	int gold = 1;
	int dame = 1;
	int id;
	float size;
};