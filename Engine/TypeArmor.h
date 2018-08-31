#pragma once
#include "TypeDame.h"
class TypeArmor
{
public:
	virtual float CalculateDame(FireDame& typeDame) = 0;
	virtual float CalculateDame(IceDame& typeDame) = 0;
	virtual float CalculateDame(LightingDame& typeDame) = 0;
	
};

class FireArmor : public TypeArmor
{
public:
	float CalculateDame(FireDame& typeDame) override
	{
		return typeDame.getDame();
	}
	float CalculateDame(IceDame& typeDame) override
	{
		return 1.5f * typeDame.getDame();
	}
	float CalculateDame(LightingDame& typeDame) override
	{
		return 0.5f * typeDame.getDame();
	}
};
class IceArmor : public TypeArmor
{
public:
	float CalculateDame(FireDame& typeDame) override
	{
		return 0.5f * typeDame.getDame();
	}
	float CalculateDame(IceDame& typeDame) override
	{
		return typeDame.getDame();
	}
	float CalculateDame(LightingDame& typeDame) override
	{
		return 1.5 * typeDame.getDame();
	}
};
class LightingArmor : public TypeArmor
{
public:
	float CalculateDame(FireDame& typeDame) override
	{
		return 1.5f * typeDame.getDame();
	}
	float CalculateDame(IceDame& typeDame) override
	{
		return 0.5 * typeDame.getDame();
	}
	float CalculateDame(LightingDame& typeDame) override
	{
		return typeDame.getDame();
	}
};