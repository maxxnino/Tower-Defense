#include "Attribute.h"
#include "DameCalculator.h"
void Attribute::ApplyDame(int type, float value)
{
	hp -= DameCalculator::GetDame(type, value, *this);
}
