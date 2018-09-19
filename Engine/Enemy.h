#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
#include "Codex.h"
#include "GameSettings.h"
#include "SpellFactory.h"
class Enemy : public PhysicObject
{
public:
	Enemy(b2World& box2DEngine, int id, float size)
		:
		PhysicObject(box2DEngine, CollisionFillter::ENEMY, CollisionFillter::BORDER |CollisionFillter::BULLET | 
			CollisionFillter::BASE | CollisionFillter::TOWER | CollisionFillter::GUIDING,
			{ -20.0f,9.5f }, true, false, size, {0.0f,0.0f}),
		id(id),
		size(size),
		offSet(int(size * Graphics::scalePixel)),
		att(GameSettings::Get().GetData("[Enemy Speed]"), GameSettings::Get().GetData("[Enemy Hp]"), GameSettings::Get().GetData("[Dame To Base]"),
			10,10,10),
		dir(1.0f,0.0f)
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

		for (auto& s : spells)
		{
			s->Draw(gfx, pos);
		}
	}
	
	bool IsReachtBase() { return isReachBase; }
	int GetGold() { return gold; }
	void Update(float dt)
	{
		UpdateSpeed(dt);
		if (isGetHit)
		{
			timerGetHit += dt;
			if (timerGetHit >= 0.03f)
			{
				timerGetHit = 0.0f;
				isGetHit = false;
			}
		}
		for (int i = 0; i < spells.size();)
		{
			if (spells[i]->GetIsRemove())
			{
				std::swap(spells[i], spells.back());
				spells.pop_back();
			}
			else
			{
				spells[i]->Update(dt, *this);
				i++;
			}
		}
	}
	void AddSpell(int spellID)
	{
		spells.emplace_back(SpellFactory::MakeSpell(spellID));
	}
	float GetDame() { return att.GetBaseAttribute(TypeAttribute::BaseDame); }
	void MarkReachBase() { isReachBase = true; }
	void SetDir(const b2Vec2& newDir)
	{
		dir = newDir;
	}
	/**********************************/
	/*Virtual function for PhysiObject*/
	int GetID() { return id; }
	void ChangeAttribute(TypeAttribute typeAttribute, float value) override
	{
		att.ChangeAttribute(typeAttribute, value);
	}
	
	void ApplyDame(int type, float dame) override
	{
		att.ApplyDame(type, dame);
		isGetHit = true;
		if (att.IsDead())
		{
			isDestroyed = true;
		}
	}
	float GetBaseAttribute(TypeAttribute type) const override
	{
		return att.GetBaseAttribute(type);
	}
	/***********************************/
private:
	void UpdateSpeed(float dt)
	{
		const float totalSpeed = att.GetTotalAttribute(TypeAttribute::MoveSpeed);
		body->ApplyLinearImpulse(body->GetMass() * dir, body->GetWorldCenter(), true);
		const float maxSpeed = totalSpeed * totalSpeed;
		const float curSpeed = (float)body->GetLinearVelocity().LengthSquared();
		if (curSpeed > maxSpeed)
		{
			body->SetLinearVelocity(sqrt(maxSpeed / curSpeed) * body->GetLinearVelocity());
		}
		
	}
private:
	bool isReachBase = false;
	bool isGetHit = false;
	Attribute att;
	std::shared_ptr<Surface> surf;
	int gold = (int)GameSettings::Get().GetData("[Gold When Killed]");
	float timerGetHit = GameSettings::Get().GetData("[Flash Time When Get Hit]");
	int offSet;
	int id;
	float size;
	std::vector<std::unique_ptr<ISpell>> spells;
	b2Vec2 dir;
};