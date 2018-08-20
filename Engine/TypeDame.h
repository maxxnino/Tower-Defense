#pragma once
#include <memory>
class TypeDame
{
public:
	virtual float getDame() = 0;
	virtual float getAttackSpeed() = 0;
	virtual std::shared_ptr<TypeDame> Clone() = 0;
protected:
	float baseAttackSpeed = 1.0f;
	float baseDame = 10.0f;
};
class FireDame : public TypeDame
{
public:
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	std::shared_ptr<TypeDame> Clone()
	{
		return std::make_shared<FireDame>();
	}
private:
	float attackSpeedMultiply = 1.0f;
	float dameMultiply = 2.0f;
};
class IceDame : public TypeDame
{
public:
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	std::shared_ptr<TypeDame> Clone()
	{
		return std::make_shared<IceDame>();
	}
private:
	float attackSpeedMultiply = 1.5f;
	float dameMultiply = 1.5f;
};
class LightingDame : public TypeDame
{
public:
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	std::shared_ptr<TypeDame> Clone()
	{
		return std::make_shared<LightingDame>();
	}
private:
	float attackSpeedMultiply = 0.5f;
	float dameMultiply = 0.75f;
};