#pragma once
#include "Colors.h"
#include <memory>
#include <assert.h>
#include <vector>
#include <algorithm>
#include "TypeDame.h"
class Tower
{
public:
	Tower(Color c)
		:
		c(c)
	{}
	const Color& GetColor() const
	{
		return c;
	}
	bool isAttack(float dt)
	{
		timer += dt;
		float totalAttackSpeed = 0.0f;
		std::for_each(typeDames.begin(), typeDames.end(), [&totalAttackSpeed](auto type) { totalAttackSpeed += type->getAttackSpeed(); });
		totalAttackSpeed /= typeDames.size();
		if (timer >= totalAttackSpeed)
		{
			timer = 0.0f;
			return true;
		}
		else
		{
			return false; 
		}
	}
	bool Upgrade(TypeDame* newType)
	{
		if (typeDames.size() >= 3)
		{
			return false;
		}
		else
		{
			typeDames.emplace_back(newType->Clone());
			switch (typeDames.size())
			{
			case 1:
				c = typeDames.back()->getColor();
				break;
			case 2:
				{
					const Color& c01 = typeDames[0]->getColor();
					const Color& c02 = typeDames[1]->getColor();
					c.SetR((c01.GetR() + c02.GetR()) / 2u);
					c.SetG((c01.GetG() + c02.GetG()) / 2u);
					c.SetB((c01.GetB() + c02.GetB()) / 2u);
				}
				break;
			case 3:
				{
					const Color& c01 = typeDames[0]->getColor();
					const Color& c02 = typeDames[1]->getColor();
					const Color& c03 = typeDames[2]->getColor();
					c.SetR((c01.GetR() + c02.GetR() + c03.GetR()) / 3u);
					c.SetG((c01.GetG() + c02.GetG() + c03.GetG()) / 3u);
					c.SetB((c01.GetB() + c02.GetB() + c03.GetB()) / 3u);
				}
				break;
			default:
				break;
			}
			return true;
		}
	}
private:
	Color c;
	int lv = 1;
	float timer = 0;
	std::vector<std::shared_ptr<TypeDame>> typeDames;
};