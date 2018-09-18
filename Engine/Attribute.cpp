#include "Attribute.h"
#include "DameCalculator.h"
void Attribute::ChangeAttribute(TypeAttribute typeAttribute, float value)
{
	switch (typeAttribute)
	{
	case MoveSpeed:
	{
		if (value > 0)
		{
			const float valueChange = maxMoveSpeed - moveSpeed - changeMoveSpeed - value;
			(value < valueChange) ? (changeMoveSpeed += value) : (changeMoveSpeed = maxMoveSpeed - moveSpeed);
		}
		else
		{
			const float valueChange = moveSpeed + changeMoveSpeed + value - minMoveSpeed;
			(value < valueChange) ? (changeMoveSpeed = minMoveSpeed - moveSpeed) : (changeMoveSpeed += value);
		}
		break;
	}	
	case Health:
	{
		changeHp += value;
		if (curHp > GetMaxHealth())
		{
			curHp = GetMaxHealth();
		}
		break;
	}	
	case BaseDame:
		changeBaseDame += value;
		break;
	default:
		assert(false);
		break;
	}
}
float Attribute::GetMoveSpeedAndDame(TypeAttribute typeAttribute) const
{
	switch (typeAttribute)
	{
	case MoveSpeed:
		return moveSpeed + changeMoveSpeed;
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
void Attribute::ApplyDame(int type, float value)
{
	curHp -= DameCalculator::GetDame(type, value, *this);
}

void Attribute::Heal(int value)
{
	curHp += value;
	const float curMaxHp = GetMaxHealth();
	if (curHp > curMaxHp)
	{
		curHp = curMaxHp;
	}
}

bool Attribute::IsDead() const
{
	return (curHp <= 0) ? true : false;
}
