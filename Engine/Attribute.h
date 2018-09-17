#pragma once
#include "Element.h"

enum TypeAttribute
{
	MoveSpeed,
	Health,
	BaseDame
};

class Attribute
{
public:	
	Attribute(float moveSpeed, float hp, float baseDame, float fireResistant, float waterResistant, float natureResistant)
		:
		fireResistant(fireResistant), waterResistant(waterResistant), natureResistant(natureResistant),
		moveSpeed(moveSpeed), hp(hp), baseDame(baseDame)
	{}
	void ChangeAttribute(TypeAttribute typeAttribute, float value)
	{
		switch (typeAttribute)
		{
		case MoveSpeed:
			changeMoveSpeed += value;
			break;
		case Health:
			changeHp += value;
			break;
		case BaseDame:
			changeBaseDame += value;
			break;
		default:
			assert(false);
			break;
		}
	}
	float GetStat(TypeAttribute typeAttribute) const
	{
		switch (typeAttribute)
		{
		case MoveSpeed:
			return moveSpeed + changeMoveSpeed;
			break;
		case Health:
			return hp + changeHp;
			break;
		case BaseDame:
			return baseDame + changeBaseDame;
			break;
		default:
			assert(false);
			return 0;
			break;
		}
	}
	
	void ApplyDame(int type, float value);
	bool IsDead() const
	{
		if (hp + changeHp <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	//base stat
	float fireResistant;
	float waterResistant;
	float natureResistant;
	float moveSpeed;
	float hp;
	float baseDame;

	//modified stat
	float mFireResistant = 0;
	float mWaterResistant = 0;
	float mNatureResistant = 0;
	float changeMoveSpeed = 0;
	float changeHp = 0;
	float changeBaseDame = 0;
};