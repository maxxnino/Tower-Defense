#pragma once
#include "Element.h"
class TypeArmor
{
public:
	virtual float CalculateDame(FireDame& element) = 0;
	virtual float CalculateDame(IceDame& element) = 0;
	virtual float CalculateDame(LightingDame& element) = 0;
	
};

class FireArmor : public TypeArmor
{
public:
	float CalculateDame(FireDame& element) override
	{
		return element.getDame();
	}
	float CalculateDame(IceDame& element) override
	{
		return 1.5f * element.getDame();
	}
	float CalculateDame(LightingDame& element) override
	{
		return 0.5f * element.getDame();
	}
};
class IceArmor : public TypeArmor
{
public:
	float CalculateDame(FireDame& element) override
	{
		return 0.5f * element.getDame();
	}
	float CalculateDame(IceDame& element) override
	{
		return element.getDame();
	}
	float CalculateDame(LightingDame& element) override
	{
		return 1.5 * element.getDame();
	}
};
class LightingArmor : public TypeArmor
{
public:
	float CalculateDame(FireDame& element) override
	{
		return 1.5f * element.getDame();
	}
	float CalculateDame(IceDame& element) override
	{
		return 0.5 * element.getDame();
	}
	float CalculateDame(LightingDame& element) override
	{
		return element.getDame();
	}
};