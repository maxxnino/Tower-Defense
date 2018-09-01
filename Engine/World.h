#pragma once
#include <unordered_map>
#include <memory>
#include <assert.h>
#include <limits>
#include "Box2D/Box2D.h"
#include "IWorldMediator.h"
#include "IComponent.h"
#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"
class World : public IWorldMediator, public IComponent
{
public:
	World(b2World& box2DEngine, int tileWidth, int tileHeight)
		:
		box2DEngine(box2DEngine),
		tileWidth(tileWidth),
		tileHeight(tileHeight),
		indexTower(0),
		indexEnemy(0),
		indexBullet(0)
	{

	}
	void Draw(Graphics& gfx)
	{
		std::for_each(enemyMgr.begin(), enemyMgr.end(), [&gfx](auto& e) {e.second->Draw(gfx); });
		std::for_each(towerMgr.begin(), towerMgr.end(), [&gfx,this](auto& t) {t.second->Draw(gfx, tileWidth, tileHeight); });
		std::for_each(bulletMgr.begin(), bulletMgr.end(), [&gfx, this](auto& b) {b.second->Draw(gfx); });
	}
	void Update(float dt)
	{
		std::for_each(towerMgr.begin(), towerMgr.end(), [dt,this](auto& t) {t.second->Update(dt); });
		timer += dt;
		if (timer >= 1.0f)
		{
			timer = 0.0f;
			MakeEnemy();
		}
	}
	void AddMediator(IMediator* mediator) override
	{
		guiAndBoardMediator = mediator;
	}
	//bullet control
	void MakeBullet(int curTarget, TypeDame* typeDame, Color c, const b2Vec2& worldPos) override
	{
		auto e = enemyMgr.find(curTarget);
		if (e != enemyMgr.end())
		{
			const b2Vec2 enemyPos =  e->second->getBody().GetPosition();
			auto b = std::make_unique<Projectile>(box2DEngine, curTarget, worldPos, bulletSize);
			b->SetVelocity(enemyPos - worldPos);
			bulletMgr.emplace(indexBullet, std::move(b));
			indexBullet++;
		}
	}
	
	//enemy control
	void MakeEnemy() override 
	{
		enemyMgr.emplace(indexEnemy, std::make_unique<Enemy>(box2DEngine, indexEnemy));
		indexEnemy++;
	}
	
	//tower control
	int MakeTower(TypeDame* typeDame, Color c, const b2Vec2& worldPos, float size = 1.0f) override
	{
		auto tower = std::make_unique<Tower>(box2DEngine, typeDame, c, worldPos, size);
		tower->AddMediator(this);
		towerMgr.emplace(indexTower, std::move(tower));
		indexTower++;
		return indexTower - 1;
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
	void UpgradeTower(TypeDame* typeDame, int towerIndex) override
	{
		auto t = towerMgr.find(towerIndex);
		if (t != towerMgr.end())
		{
			t->second->Upgrade(typeDame);
		}
		else
		{
			assert(false);
		}
	}
	int GetTargetEnemy(std::set<int>& enemyIDs,const b2Vec2& towerPos)
	{
		int targetID = -1;
		float curLen = std::numeric_limits<float>::max();
		std::for_each(enemyIDs.begin(), enemyIDs.end(), [&](int const& id) {
			auto e = enemyMgr.find(id);
			if (e != enemyMgr.end())
			{
				if (!e->second->isRemove())
				{
					const float newLen = (float)(e->second->getBody().GetPosition() - towerPos).LengthSquared();
					if (newLen < curLen)
					{
						targetID = e->second->GetID();
						curLen = newLen;
					}
				}
				
			}
		});
		return targetID;
	}
private:
	int tileWidth;
	int tileHeight;
	float timer = 0.0f;
	static constexpr float bulletSize = 0.5f;
	b2World& box2DEngine;
	IMediator* guiAndBoardMediator = nullptr;
	std::unordered_map<int, std::unique_ptr<Tower>> towerMgr;
	std::unordered_map<int, std::unique_ptr<Enemy>> enemyMgr;
	std::unordered_map<int, std::unique_ptr<Projectile>> bulletMgr;
	int indexTower;
	int indexEnemy;
	int indexBullet;
};