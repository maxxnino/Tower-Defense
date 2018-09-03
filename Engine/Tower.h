#pragma once
#include <vector>
#include <set>
#include "PhysicObject.h"
#include "TypeDame.h"
#include "Colors.h"
#include "IWordComponent.h"
class Tower : public PhysicObject, public IWorldComponent
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
	void Draw(Graphics& gfx, int tileWidth, int tileHeight)
	{
		gfx.DrawRectDim(gfx.ToScreenSpace(body->GetPosition()) + VecI(2, 2), tileWidth - 2, tileHeight - 2, c);
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
			if (curTarget == -1)
			{
				if (enemyIDs.size() > 0)
				{
					curTarget = wordMediator->GetTargetEnemy(enemyIDs, body->GetPosition());
					if (curTarget != -1)
					{
						wordMediator->MakeBullet(curTarget, typeDames[0], typeDames[0]->getColor(), body->GetPosition());
					}
				}
			}
			else
			{
				wordMediator->MakeBullet(curTarget, typeDames[0], typeDames[0]->getColor(),body->GetPosition());
			}
		}
	}
	void Upgrade(TypeDame* newType)
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
	bool IsMaxLv()
	{
		return typeDames.size() >= 3;
	}
	inline int GetGold() const noexcept
	{
		return typeDames[0]->GetGold();
	}
	
	//Add World mediation
	void AddMediator(IWorldMediator* wordMediator) override
	{
		if (this->wordMediator == nullptr)
		{
			this->wordMediator = wordMediator;
		}
	}


	/**********************************/
	/*Virtual function for PhysiObject*/
	void RemoveEnemyID(int id) override
	{
		assert(enemyIDs.find(id) != enemyIDs.end());
		enemyIDs.erase(id);
		if (id == curTarget)
		{
			curTarget = -1;
		}
	}
	void AddEnemyID(int id) override
	{
		enemyIDs.insert(id);
	}
	/***********************************/
private:
	Color c;
	float timer = 0;
	IWorldMediator* wordMediator = nullptr;
	std::vector<TypeDame*> typeDames;
	std::set<int> enemyIDs;
	int curTarget = -1;
};