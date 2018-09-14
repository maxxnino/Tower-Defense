#pragma once
#include "Enemy.h"
#include "SharedAnimation.h"
class Skill;
class SkillState
{
public:
	virtual void Update(float dt, Enemy& enemy, Skill* skill) = 0;
	virtual std::unique_ptr<SkillState> Clone() const = 0;
	void Draw(Graphics& gfx, const b2Vec2& offSet) const
	{
		animation.DrawAlpha(Graphics::ToScreenSpace(pos - offSet), gfx);
	}
protected:
	SkillState(const SharedAnimationData* data)
		:
		animation(data)
	{}
	void UpdateAnimation(float dt)
	{
		animation.Update(dt);
	}
protected:
	SharedAnimation animation;
	b2Vec2 pos;
};

class DameOverTime : public SkillState
{
public:
	DameOverTime(float Dps, float duration, const SharedAnimationData* data)
		:
		SkillState(data),
		duration(duration),
		Dps(Dps)
	{}
	void Update(float dt, Enemy& enemy, Skill* skill) override;
	std::unique_ptr<SkillState> Clone() const override
	{
		return std::make_unique<DameOverTime>(Dps, duration, animation.GetAnimationData());
	}
private:
	float timer = 0.0f;
	float timerDuration = 0.0f;
	float duration;
	float Dps;
};