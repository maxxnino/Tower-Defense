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
		PhysicObject(box2DEngine, CollisionFillter::TOWER, CollisionFillter::ENEMY, worldPos, true, true, size, b2Vec2( 0.0f,0.0f ))
	{
		Upgrade(element);
		body->SetUserData(this);
	}
	void Draw(Graphics& gfx, int tileWidth, int tileHeight)
	{
		//gfx.DrawRectDim(gfx.ToScreenSpace(body->GetPosition()) + VecI(2, 2), tileWidth - 2, tileHeight - 2, c);
		const VecI pos = gfx.ToScreenSpace(body->GetPosition());
		gfx.DrawSprite(pos.x, pos.y, *element->GetSurface(), SpriteEffect::AlphaBlendBaked{});
	}
	inline const Color& GetColor() const noexcept
	{
		return c;
	}
	void Update(float dt) noexcept
	{
		timer += dt;
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
	Element* element;
	std::set<int> enemyIDs;
	int curTarget = -1;
};