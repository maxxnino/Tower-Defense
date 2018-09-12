#pragma once
#include "Colors.h"
#include "SharedAnimation.h"
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
	Element(int type,int lv, float attackSpeedMultiply, float dameMultiply, Color c, const Surface* surf, const SharedAnimationData* projectileAnimation)
		:
		attackSpeedMultiply(attackSpeedMultiply),
		dameMultiply(dameMultiply),
		c(c),
		surf(surf),
		projectileAnimation(projectileAnimation),
		type(type),
		lv(lv)
	{}
	float getDame()
	{
		return baseAttackSpeed * dameMultiply;
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
	const Surface* GetSurface()
	{
		return surf;
	}
	const Surface* GetElementSurface()
	{
		return element;
	}
	const SharedAnimationData* GetProjectileAnimation()
	{
		return projectileAnimation;
	}
	void SetElementSurface(const Surface* surf)
	{
		element = surf;
	}
protected:
	float baseAttackSpeed = 1.0f;
	int baseGold = 5;
	float baseDame = 10.0f;
	float attackSpeedMultiply;
	float dameMultiply;
	Color c;
	const Surface* surf;
	const Surface* element;
	const SharedAnimationData* projectileAnimation;
	const 
	int type;
	int lv;
};