#pragma once
#include <memory>
#include "Colors.h"
#include "IDataItem.h"
#include "Box2D/Box2D.h"
class TypeDame : public IDataItem
{
public:
	TypeDame(b2World& box2DEngine, float attackSpeedMultiply, float dameMultiply, Color c)
		:
		box2DEngine(box2DEngine),
		attackSpeedMultiply(attackSpeedMultiply),
		dameMultiply(dameMultiply),
		c(c)
	{}
	virtual float getDame() = 0;
	virtual float getAttackSpeed() = 0;
	Color getColor() override
	{
		return c;
	}
	void executed(TileGame* tileGame) override;
	b2World& GetBox2DEngine()
	{
		return box2DEngine;
	}
protected:
	float baseAttackSpeed = 1.0f;
	float baseDame = 10.0f;
	float attackSpeedMultiply;
	float dameMultiply;
	Color c;
	b2World& box2DEngine;
};
class FireDame : public TypeDame
{
public:
	FireDame(b2World& box2DEngine)
		:
		TypeDame(box2DEngine, 1.0f, 2.0f,Colors::Red)
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
	IceDame(b2World& box2DEngine)
		:
		TypeDame(box2DEngine, 1.5f, 1.5f, Colors::Green)
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
	LightingDame(b2World& box2DEngine)
		:
		TypeDame(box2DEngine, 0.5f, 0.75f, Colors::Blue)
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