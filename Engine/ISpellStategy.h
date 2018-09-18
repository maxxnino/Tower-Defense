#pragma once
#include "PhysicObject.h"
#include "SharedAnimation.h"
#include "ChiliMath.h"
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
	void MarkRemove(PhysicObject& entity)
	{
		if (!isRemove)
		{
			isRemove = true;
			OnRemove(entity);
		}

	}
	virtual std::unique_ptr<ISpellStategy> Clone() const = 0;
	virtual void EntityChangeData(PhysicObject& entity) {};
protected:
	ISpellStategy(const SharedAnimationData* data, float duration)
		:
		animation(data),
		duration(duration)
	{}
private:
	virtual void OnRemove(PhysicObject& entity) {};
	virtual void DoSomethingToEnemy(float dt, PhysicObject& entity) {};
protected:
	float duration;
	float timerDuration = 0.0f;
	SharedAnimation animation;
private:
	bool isRemove = false;
	b2Vec2 pos;
	
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
	std::unique_ptr<ISpellStategy> Clone() const override
	{
		return std::make_unique<DameOverTime>(animation.GetAnimationData(), type, Dps, duration);
	}
private:
	void DoSomethingToEnemy(float dt, PhysicObject& entity) override
	{
		const float moveSpeed = entity.GetMoveSpeedAndDame(TypeAttribute::MoveSpeed);
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

class SlowMovementSpeed : public ISpellStategy
{
public:
	SlowMovementSpeed(const SharedAnimationData* data, float slowPercent, float duration)
		:
		ISpellStategy(data, duration),
		type(type),
		slowPercent(slowPercent)
	{}
	std::unique_ptr<ISpellStategy> Clone() const override
	{
		return std::make_unique<SlowMovementSpeed>(animation.GetAnimationData(), slowPercent, duration);
	}
private:
	void DoSomethingToEnemy(float dt, PhysicObject& entity) override
	{
		const float changeInValue = slowPercent * entity.GetMoveSpeedAndDame(TypeAttribute::MoveSpeed);
		const float slowAmount = EaseOut(timerDuration, 0.0f, changeInValue, duration);
		entity.ChangeAttribute(TypeAttribute::MoveSpeed, -slowAmount);
		curTotalSpeedSlow += slowAmount;
	}
	void OnRemove(PhysicObject& entity) override
	{
		entity.ChangeAttribute(TypeAttribute::MoveSpeed, curTotalSpeedSlow);
	}
private:
	float slowPercent;
	float curTotalSpeedSlow = 0.0f;
	Element::Type type;
};