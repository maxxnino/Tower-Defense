#pragma once
#include "PhysicObject.h"
#include "SharedAnimation.h"
class ISpellStategy
{
public:
	void Update(float dt, PhysicObject& entity)
	{
		animation.Update(dt);
		timerDuration += dt;
		if (timerDuration <= duration)
		{
			DoSomethingToEnemy(dt, entity);
			pos = entity.getBody().GetPosition();
		}
		else
		{
			MarkRemove(entity);
		}
	}
	void Draw(Graphics& gfx, const b2Vec2& offSet) const
	{
		animation.DrawAlpha(Graphics::ToScreenSpace(pos - offSet), gfx);
	}
	bool IsRemove() const
	{
		return isRemove;
	}

	virtual void EntityChangeData(PhysicObject& entity) {};
protected:
	ISpellStategy(const SharedAnimationData* data, float duration)
		:
		animation(data),
		duration(duration)
	{}
	void MarkRemove(PhysicObject& entity)
	{
		if (!isRemove)
		{
			isRemove = true;
			OnRemove(entity);
		}
		
	}
private:
	virtual void OnRemove(PhysicObject& entity) {};
	virtual void DoSomethingToEnemy(float dt, PhysicObject& entity) {};
private:
	bool isRemove = false;
	float duration;
	float timerDuration = 0.0f;
	b2Vec2 pos;
	SharedAnimation animation;
};

class DameOverTime : public ISpellStategy
{
public:
	DameOverTime(const SharedAnimationData* data, Element::Type type, float Dps, float duration)
		:
		ISpellStategy(data, duration),
		type(type),
		Dps(Dps)
	{}
private:
	void DoSomethingToEnemy(float dt, PhysicObject& entity) override
	{
		timer += dt;
		while (timer >= 1.0f)
		{
			entity.ApplyDame(type, Dps);
			timer -= 1.0f;
		}
	}
private:
	float timer = 0.0f;
	float Dps;
	Element::Type type;
};