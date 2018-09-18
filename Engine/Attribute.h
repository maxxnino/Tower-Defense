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
	Attribute(float moveSpeed, float maxHp, float baseDame, float fireResistant, float waterResistant, float natureResistant)
		:
		fireResistant(fireResistant), waterResistant(waterResistant), natureResistant(natureResistant),
		moveSpeed(moveSpeed), maxHp(maxHp), baseDame(baseDame)
	{}
	inline float GetMaxHealth() const
	{
		return maxHp + changeHp;
	}
	inline float GetCurHealth() const
	{
		return curHp;
	}
	float GetMoveSpeedAndDame(TypeAttribute typeAttribute) const;
	bool IsDead() const;
	void ChangeAttribute(TypeAttribute typeAttribute, float value);
	void ApplyDame(int type, float value);
	void Heal(int value);
	
public:
	//base stat
	float fireResistant;
	float waterResistant;
	float natureResistant;
	float mFireResistant = 0;
	float mWaterResistant = 0;
	float mNatureResistant = 0;
private:
	static constexpr float minMoveSpeed = 1.0f;
	static constexpr float maxMoveSpeed = 15.0f;
	float moveSpeed;
	float maxHp;
	float curHp = maxHp;
	float baseDame;

	float changeMoveSpeed = 0;
	float changeHp = 0;
	float changeBaseDame = 0;
};