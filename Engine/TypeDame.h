#pragma once
#include "Projectile.h"
#include "Colors.h"
class TypeDame
{
public:
	TypeDame(float attackSpeedMultiply, float dameMultiply, Color c)
		:
		attackSpeedMultiply(attackSpeedMultiply),
		dameMultiply(dameMultiply),
		c(c)
	{}
	virtual float getDame() = 0;
	virtual float getAttackSpeed() = 0;
	virtual int GetGold() const = 0;
	inline const Color& getColor() const noexcept
	{
		return c;
	}
	inline Color getColor() noexcept
	{
		return c;
	}
protected:
	float baseAttackSpeed = 1.0f;
	int baseGold = 5;
	float baseDame = 10.0f;
	float attackSpeedMultiply;
	float dameMultiply;
	Color c;
};
class FireDame : public TypeDame
{
public:
	FireDame()
		:
		TypeDame(1.0f, 2.0f,Colors::Red)
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold - 3;
	}
};
class IceDame : public TypeDame
{
public:
	IceDame()
		:
		TypeDame(1.5f, 1.5f, Colors::Green)
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold - 2;
	}
};
class LightingDame : public TypeDame
{
public:
	LightingDame()
		:
		TypeDame(0.5f, 0.75f, Colors::Blue)
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold;
	}
};