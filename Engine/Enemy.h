#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
#include "Codex.h"
#include "GameSettings.h"
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
			surf = Codex<Surface>::Retrieve(L"Images\\Enemy\\pm_enemy_03.png");
		}
		else if ((id % 2) == 0)
		{
			surf = Codex<Surface>::Retrieve(L"Images\\Enemy\\pm_enemy_02.png");
		}
		else
		{
			surf = Codex<Surface>::Retrieve(L"Images\\Enemy\\pm_enemy_01.png");
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

		//draw collsion circle
		//gfx.DrawCircle(body->GetPosition(), size, Colors::Blue);
	}
	
	bool IsReachtBase() { return isReachBase; }
	int GetGold() { return gold; }
	void Update(float dt)
	{
		const b2Vec2 vel = body->GetLinearVelocity();
		const float velChange = 6 - vel.x;
		const float impulse = body->GetMass() * velChange; //disregard time factor
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
	float timerGetHit = GameSettings::Get().GetData("[Flash Time When Get Hit]");
	b2Vec2 speed = { GameSettings::Get().GetData("[Enemy Speed]"),0.0f};
	const Surface* surf;
	int offSet;
	int Hp = (int)GameSettings::Get().GetData("[Enemy Hp]");
	int gold = (int)GameSettings::Get().GetData("[Gold When Killed]");
	int dame = (int)GameSettings::Get().GetData("[Dame To Base]");
	int id;
	float size;
};