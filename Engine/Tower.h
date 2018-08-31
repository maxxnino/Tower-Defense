#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <set>
#include "TypeDame.h"
#include "Colors.h"
#include "Projectile.h"
#include "Enemy.h"
class Tower //: public PhysicObject
{
public:
	Tower(Color c, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f })
		:
		c(c)
		//PhysicObject(box2DEngine, CollisionFillter::TOWER, CollisionFillter::ENEMY, worldPos, true, true, size, linVel)
	{
		//body->SetUserData(this);
	}
	inline const Color& GetColor() const noexcept
	{
		return c;
	}
	void Update(float dt) noexcept;
	bool GetAttack()
	{
		return isAttack;
	}
	void Upgrade(TypeDame* newType);
	void AddEnemy(Enemy* enemy)
	{
		enemies.insert(enemy);
	}
	void RemoveEnemy(Enemy* enemy)
	{
		if (enemies.size() != 0)
		{
			enemies.erase(enemy);
		}
	}
private:
	Color c;
	int lv = 1;
	float timer = 0;
	bool isAttack = false;
	std::vector<TypeDame*> typeDames;
	std::set<Enemy*> enemies;
};