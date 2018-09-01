#pragma once
#include <vector>
#include "PhysicObject.h"
#include "TypeDame.h"
#include "Colors.h"
class Tower : public PhysicObject
{
public:
	Tower(b2World& box2DEngine,TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f )
		:
		c(c),
		PhysicObject(box2DEngine, CollisionFillter::TOWER, CollisionFillter::ENEMY, worldPos, true, true, size, b2Vec2( 0.0f,0.0f ))
	{
		Upgrade(typeDame);
		body->SetUserData(this);
	}
	inline const Color& GetColor() const noexcept
	{
		return c;
	}
	void Update(float dt) noexcept
	{
		timer += dt;
		float totalAttackSpeed = 0.0f;
		std::for_each(typeDames.begin(), typeDames.end(), [&totalAttackSpeed](auto type) { totalAttackSpeed += type->getAttackSpeed(); });
		totalAttackSpeed /= typeDames.size();
		if (timer >= totalAttackSpeed)
		{
			timer = 0.0f;
			isAttack = true;
			/*if (enemies.size() != 0)
			{

			}*/

		}
		else
		{
			isAttack = false;
		}
	}
	bool GetAttack()
	{
		return isAttack;
	}
	Color& Upgrade(TypeDame* newType)
	{
		if (typeDames.size() >= 3)
		{
			return c;
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
		return c;
	}
	bool IsMaxLv()
	{
		return typeDames.size() >= 3;
	}
private:
	Color c;
	int lv = 1;
	float timer = 0;
	bool isAttack = false;
	std::vector<TypeDame*> typeDames;
};