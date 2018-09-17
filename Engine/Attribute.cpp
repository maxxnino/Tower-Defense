#include "Attribute.h"
#include "DameCalculator.h"
void Attribute::ApplyDame(int type, float value)
{
	curHp -= DameCalculator::GetDame(type, value, *this);
}
