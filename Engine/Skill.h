#pragma once
#include "Enemy.h"
#include "SkillState.h"
#include "Graphics.h"
#include <memory>
class Skill
{
public:
	Skill(std::unique_ptr<SkillState> state)
		:
		state(std::move(state))
	{}
	void Update(float dt, Enemy& enemy)
	{
		state->Update(dt, enemy, this);
	}
	void Draw(Graphics& gfx) const
	{
		state->Draw(gfx, offSet);
	}
	int GetEnemyID() const
	{
		return enemyID;
	}
	void AddEnemyID(int id)
	{
		enemyID = id;
	}
	void MarkRemove()
	{
		isRemove = true;
	}
	bool GetIsRemove() const
	{
		return isRemove;
	}
	void AddOffSet(const b2Vec2& pos)
	{
		offSet = pos;
	}
	std::unique_ptr<Skill> Clone() const
	{
		return std::make_unique<Skill>(state->Clone());
	}
private:
	b2Vec2 offSet;
	int enemyID = 0;
	bool isRemove = false;
	std::unique_ptr<SkillState> state;
};