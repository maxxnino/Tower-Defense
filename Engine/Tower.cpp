#include "Tower.h"
void Tower::Update(float dt) noexcept
{
	timer += dt;
	float totalAttackSpeed = 0.0f;
	std::for_each(typeDames.begin(), typeDames.end(), [&totalAttackSpeed](auto type) { totalAttackSpeed += type->getAttackSpeed(); });
	totalAttackSpeed /= typeDames.size();
	if (timer >= totalAttackSpeed)
	{
		timer = 0.0f;
		isAttack = true;
		if (enemies.size() != 0)
		{

		}
		
	}
	else
	{
		isAttack = false;
	}
}

void Tower::Upgrade(const TypeDame * newType)
{
	if (typeDames.size() >= 3)
	{
		return;
	}
	else
	{
		typeDames.emplace_back(newType);
		switch (typeDames.size())
		{
		case 1:
			c = typeDames.back()->getColor();
			break;
		case 2:
		{
			const Color& c02 = typeDames[1]->getColor();
			if (c.dword == c02.dword)
			{
				c.SetR((c.GetR() + c02.GetR()) / 3u);
				c.SetG((c.GetG() + c02.GetG()) / 3u);
				c.SetB((c.GetB() + c02.GetB()) / 3u);
			}
			else
			{
				c.SetR((c.GetR() + c02.GetR()) / 2u);
				c.SetG((c.GetG() + c02.GetG()) / 2u);
				c.SetB((c.GetB() + c02.GetB()) / 2u);
			}

		}
		break;
		case 3:
		{
			const Color& c03 = typeDames[2]->getColor();
			if (c.dword == c03.dword * 2u / 3u)
			{
				c.SetR((c.GetR() + c03.GetR()) / 3u);
				c.SetG((c.GetG() + c03.GetG()) / 3u);
				c.SetB((c.GetB() + c03.GetB()) / 3u);
			}
			else
			{
				c.SetR((c.GetR() + c03.GetR()) / 2u);
				c.SetG((c.GetG() + c03.GetG()) / 2u);
				c.SetB((c.GetB() + c03.GetB()) / 2u);
			}
		}
		break;
		default:
			break;
		}
	}
}
