#pragma once
#include <memory>
#include <vector>
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
protected:
	float baseAttackSpeed = 1.0f;
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
};