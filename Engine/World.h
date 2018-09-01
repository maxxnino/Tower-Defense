#pragma once
#include <unordered_map>
#include <memory>
#include <assert.h>
#include "Box2D/Box2D.h"
#include "IWorldMediator.h"
#include "IComponent.h"
#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"
class World : public IWorldMediator, public IComponent
{
public:
	World(b2World& box2DEngine)
		:
		box2DEngine(box2DEngine),
		indexTower(0),
		indexEnemy(0),
		indexBullet(0)
	{

	}
	void Draw(Graphics& gfx)
	{
		std::for_each(enemyMgr.begin(), enemyMgr.end(), [&gfx](auto& e) {e.second->Draw(gfx); });
	}
	void AddMediator(IMediator* mediator) override
	{
		guiAndBoardMediator = mediator;
	}
	std::pair<int, Color> MakeTower(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f) override
	{
		towerMgr.emplace(indexTower, std::make_unique<Tower>(box2DEngine, typeDame, c, worldPos, size));
		indexTower++;
		return std::move(std::make_pair<int, Color>(indexTower - 1, typeDame->getColor()));
	}
	int MakeEnemy() override 
	{
		enemyMgr.emplace(indexEnemy, std::make_unique<Enemy>(box2DEngine));
		indexEnemy++;
		return indexEnemy - 1;
	}
	int MakeBullet(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f }) override 
	{
		indexBullet++;
		return indexBullet - 1;
	}
	
	bool IsTowerMaxLv(int towerIndex) override
	{
		auto t = towerMgr.find(towerIndex);
		if (t != towerMgr.end())
		{
			return t->second->IsMaxLv();
		}
		else
		{
			assert(false);
			return true;
		}
	}
	Color UpgradeTower(TypeDame* typeDame, int towerIndex) override
	{
		auto t = towerMgr.find(towerIndex);
		if (t != towerMgr.end())
		{
			return t->second->Upgrade(typeDame);
		}
		else
		{
			assert(false);
			return Colors::Black;
		}
	}
private:
	b2World& box2DEngine;
	IMediator* guiAndBoardMediator = nullptr;
	std::unordered_map<int, std::unique_ptr<Tower>> towerMgr;
	std::unordered_map<int, std::unique_ptr<Enemy>> enemyMgr;
	std::unordered_map<int, std::unique_ptr<Projectile>> bulletMgr;
	int indexTower;
	int indexEnemy;
	int indexBullet;
};