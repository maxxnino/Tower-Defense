#pragma once
#include <vector>
#include <set>
#include "PhysicObject.h"
#include "Element.h"
#include "Colors.h"
#include "IWordComponent.h"
class Tower : public PhysicObject, public IWorldComponent
{
public:
	Tower(b2World& box2DEngine,Element* element, Color c, const b2Vec2& worldPos, float size = 1.0f )
		:
		c(c),
		PhysicObject(box2DEngine, CollisionFillter::TOWER, CollisionFillter::ENEMY, worldPos, true, true, size, b2Vec2( 0.0f,0.0f )),
		animation(element->GetTowerAnimation())
	{
		Upgrade(element);
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx, int tileWidth, int tileHeight)
	{
		const VecI pos = gfx.ToScreenSpace(body->GetPosition());
		animation.DrawAlpha(pos, gfx, mirrored);
	}
	inline const Color& GetColor() const noexcept
	{
		return c;
	}
	void Update(float dt) noexcept
	{
		timer += dt;
		animation.Update(dt);
		if (timer >= element->getAttackSpeed())
		{
			timer = 0.0f;
			if (curTarget == -1)
			{
				if (enemyIDs.size() > 0)
				{
					curTarget = wordMediator->GetTargetEnemy(enemyIDs, body->GetPosition());
					if (curTarget != -1)
					{
						wordMediator->MakeBullet(curTarget, element, element->getColor(), body->GetPosition());
					}
				}
			}
			else
			{
				wordMediator->MakeBullet(curTarget, element, element->getColor(),body->GetPosition());
			}
		}
	}
	void Upgrade(Element* newType)
	{
		element = newType;
		animation.ChangeAnimation(element->GetTowerAnimation());
	}
	bool IsMaxLv()
	{
		return element->GetLv() >= 2;
	}
	inline int GetGold() const noexcept
	{
		return element->GetGold();
	}
	Element* getCurElement()
	{
		return element;
	}
	//Add World mediation
	void AddMediator(IWorldMediator* wordMediator) override
	{
		if (this->wordMediator == nullptr)
		{
			this->wordMediator = wordMediator;
		}
	}
	void Mirrored() { mirrored = true; }
	void UnMirrored() { mirrored = false; }
	void RemoveEnemyID(int id)
	{
		assert(enemyIDs.find(id) != enemyIDs.end());
		enemyIDs.erase(id);
		if (id == curTarget)
		{
			curTarget = -1;
		}
	}
	void AddEnemyID(int id)
	{
		enemyIDs.insert(id);
	}
private:
	Color c;
	float timer = 0;
	IWorldMediator* wordMediator = nullptr;
	Element* element;
	SharedAnimation animation;
	std::set<int> enemyIDs;
	int curTarget = -1;
	bool mirrored = false;
};