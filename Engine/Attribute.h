#pragma once
#include "Element.h"
#include "GameSettings.h"
enum TypeAttribute
{
	MoveSpeed,
	Health,
	BaseDame
};

class Attribute
{
public:	
	Attribute(float baseMoveSpeed, float baseHp, float baseDame, float fireResistant, float waterResistant, float natureResistant)
		:
		fireResistant(fireResistant), waterResistant(waterResistant), natureResistant(natureResistant),
		baseMoveSpeed(baseMoveSpeed), baseHp(baseHp), baseDame(baseDame)
	{}
	inline float GetCurHealth() const
	{
		return curHp;
	}
	float GetTotalAttribute(TypeAttribute typeAttribute) const
	{
		switch (typeAttribute)
		{
		case MoveSpeed:
		{
			const float totalMoveSpeed = baseMoveSpeed + modifiedMoveSpeed;
			if (totalMoveSpeed < minMoveSpeed)
			{
				return minMoveSpeed;
			}
			if (totalMoveSpeed > maxMoveSpeed)
			{
				return maxMoveSpeed;
			}
			return totalMoveSpeed;
			break;
		}
		case Health:
		{
			const float totalHp = baseHp + modifiedHp;
			if (totalHp < 1)
			{
				return 1;
			}
			else
			{
				return totalHp;
			}
			break;
		}
		case BaseDame:
			return baseDame + modifiedBaseDame;
			break;
		default:
			assert(false);
			return 0.0f;
			break;
		}
	}
	float GetBaseAttribute(TypeAttribute typeAttribute) const
	{
		switch (typeAttribute)
		{
		case MoveSpeed:
			return baseMoveSpeed;
			break;
		case BaseDame:
			return baseDame;
			break;
		case Health:
			return baseHp;
			break;
		default:
			assert(false);
			return 0;
			break;
		}
	}
	float GetTotalResistant(Element::Type elementType) const
	{
		switch (elementType)
		{
		case Element::Fire:
			return fireResistant + mFireResistant;
			break;
		case Element::Water:
			return waterResistant + mWaterResistant;
			break;
		case Element::Nature:
			return natureResistant + mNatureResistant;
			break;
		default:
			assert(false);
			return 0.0f;
			break;
		}
	}
	bool IsDead() const;
	void ChangeAttribute(TypeAttribute typeAttribute, float value)
	{
		switch (typeAttribute)
		{
		case MoveSpeed:
		{
			modifiedMoveSpeed += value;
		}
		case Health:
		{
			modifiedHp += value;
			if (baseHp + modifiedHp <= 0 && curHp > 1)
			{
				curHp = 1;
			}
			break;
		}
		case BaseDame:
			modifiedBaseDame += value;
			break;
		default:
			assert(false);
			break;
		}
	}
	void ApplyDame(int type, float value);
	void Heal(int value);
private:
	static constexpr float minMoveSpeed = 2.0f;
	static constexpr float maxMoveSpeed = 15.0f;
	float baseMoveSpeed;
	float baseDame;
	float baseHp;
	float curHp = baseHp;
	float fireResistant;
	float waterResistant;
	float natureResistant;

	float mFireResistant = 0;
	float mWaterResistant = 0;
	float mNatureResistant = 0;
	float modifiedMoveSpeed = 0;
	float modifiedHp = 0;
	float modifiedBaseDame = 0;
};