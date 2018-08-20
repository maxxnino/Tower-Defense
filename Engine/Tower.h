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
		switch (typeDames.size())
		{
		case 0:
			return c;
			break;
		case 1:
			return Colors::Blue;
			break;
		case 2:
			return Colors::Green;
			break;
		case 3:
			return Colors::Magenta;
			break;
		default:
			return c;
			break;
		}
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
			return true;
		}
	}
private:
	Color c;
	int lv = 1;
	float timer = 0;
	std::vector<std::shared_ptr<TypeDame>> typeDames;
};