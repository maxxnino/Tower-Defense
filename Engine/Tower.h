#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <set>
#include "TypeDame.h"
#include "Colors.h"
#include "Projectile.h"
#include "Enemy.h"
#include "IObservable.h"
class Tower : public PhysicObject, public IObervable
{
public:
	Tower(b2World& box2DEngine,Color c, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f })
		:
		c(c),
		PhysicObject(box2DEngine, CollisionFillter::TOWER, CollisionFillter::ENEMY, worldPos, true, true, size, linVel)
	{
		body->SetUserData(this);
	}
	inline const Color& GetColor() const noexcept
	{
		return c;
	}
	void Update(float dt) noexcept;
	void OnNotify(class Observer* obs) override
	{
		RemoveEnemy(static_cast<Enemy*>(obs));
	}
	bool GetAttack()
	{
		return isAttack;
	}
	bool Upgrade(TypeDame* newType);
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
	void RemoveAll()
	{
		for (auto e : enemies)
		{
			e->RemoveObs(this);
		}
		enemies.clear();
	}
private:
	Color c;
	int lv = 1;
	float timer = 0;
	bool isAttack = false;
	std::vector<TypeDame*> typeDames;
	std::set<Enemy*> enemies;
};