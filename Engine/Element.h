#pragma once
#include "Colors.h"
#include "SharedAnimation.h"
#include "GameSettings.h"
#include "Skill.h"
class Element
{
public:
	enum Type
	{
		None = 0,
		Fire = 1,
		Water = 10,
		Nature = 100
	};
public:
	Element(int type,int lv, float attackSpeedMultiply, float dameMultiply, Color c, const SharedAnimationData* towerAnimation, 
		const SharedAnimationData* projectileAnimation, std::unique_ptr<SkillState> state)
		:
		attackSpeedMultiply(attackSpeedMultiply),
		dameMultiply(dameMultiply),
		c(c),
		towerAnimation(towerAnimation),
		projectileAnimation(projectileAnimation),
		type(type),
		lv(lv),
		skill(std::move(state))
	{}
	float getDame()
	{
		return baseDame * dameMultiply;
	}
	float getAttackSpeed()
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const
	{
		return baseGold;
	}
	int GetLv() 
	{ 
		return lv;
	}
	int getType()
	{
		return type;
	}
	inline const Color& getColor() const noexcept
	{
		return c;
	}
	inline Color getColor() noexcept
	{
		return c;
	}
	const SharedAnimationData* GetTowerAnimation()
	{
		return towerAnimation;
	}
	const std::shared_ptr<Surface> GetElementSurface()
	{
		return element;
	}
	const SharedAnimationData* GetProjectileAnimation()
	{
		return projectileAnimation;
	}
	std::unique_ptr<Skill> CloneSkill() const 
	{
		return skill.Clone();
	}
	void SetElementSurface(const std::shared_ptr<Surface> surf)
	{
		element = surf;
	}
protected:
	float baseAttackSpeed = GameSettings::Get().GetData("[Tower Base Attack Speed]");
	int baseGold = (int)GameSettings::Get().GetData("[Tower Base Gold Cost]");
	float baseDame = GameSettings::Get().GetData("[Tower Base Dame]");
	float attackSpeedMultiply;
	float dameMultiply;
	Color c;
	std::shared_ptr<Surface> element;
	const SharedAnimationData* towerAnimation;
	const SharedAnimationData* projectileAnimation;
	const Skill skill;
	const 
	int type;
	int lv;
};