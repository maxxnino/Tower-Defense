#include "Attribute.h"
#include "DameCalculator.h"
void Attribute::ApplyDame(int type, float value)
{
	curHp -= DameCalculator::GetDame(type, value, *this);
}

void Attribute::Heal(int value)
{
	curHp += value;
	const float curMaxHp = GetTotalAttribute(TypeAttribute::Health);
	if (curHp > curMaxHp)
	{
		curHp = curMaxHp;
	}
}

bool Attribute::IsDead() const
{
	return (curHp <= 0) ? true : false;
}
