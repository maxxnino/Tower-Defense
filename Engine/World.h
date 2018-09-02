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
#include "LineWall.h"
class World : public IWorldMediator, public IComponent
{
public:
	World(b2World& box2DEngine, int tileWidth, int tileHeight)
		:
		box2DEngine(box2DEngine),
		border(box2DEngine),
		tileWidth(tileWidth),
		tileHeight(tileHeight),
		posOffSet(float32(tileWidth / (Graphics::scalePixel * 2)), float32(-tileHeight / (Graphics::scalePixel * 2))),
		indexTower(0),
		indexEnemy(0)
	{

	}
	/**********************************/
	/*          World Control         */
	void AddMediator(IMediator* mediator) override
	{
		guiAndBoardMediator = mediator;
	}
	void Draw(Graphics& gfx)
	{
		std::for_each(enemyMgr.begin(), enemyMgr.end(), [&gfx](auto& e) {e.second->Draw(gfx); });
		std::for_each(towerMgr.begin(), towerMgr.end(), [&gfx,this](auto& t) {t.second->Draw(gfx, tileWidth, tileHeight); });
		for (auto& b : bulletMgr)
		{
			b->Draw(gfx);
		}
	}
	void Update(float dt)
	{
		std::for_each(towerMgr.begin(), towerMgr.end(), [dt,this](auto& t) {t.second->Update(dt); });
		for (int i = 0; i < bulletMgr.size();)
		{
			if (bulletMgr[i]->IsRemove())
			{
				std::swap(bulletMgr[i], bulletMgr.back());
				bulletMgr.pop_back();
			}
			else
			{
				if (bulletMgr[i]->GetEnemyID() != -1)
				{
					auto enemy = enemyMgr.find(bulletMgr[i]->GetEnemyID());
					bulletMgr[i]->SetVelocity(enemy->second->getBody().GetPosition() - bulletMgr[i]->getBody().GetPosition());
					i++;
				}
				else
				{
					bulletMgr[i]->MarkDead();
				}
			}
		}
		timer += dt;
		if (timer >= 1.5f)
		{
			timer = 0.0f;
			MakeEnemy();
		}
	}
	void ClearWorld()
	{
		for (int i = 0; i < bulletMgr.size();)
		{
			if (bulletMgr[i]->IsRemove())
			{
				std::swap(bulletMgr[i], bulletMgr.back());
				bulletMgr.pop_back();
			}
			else
			{
				i++;
			}
		}
	}
	/**********************************/


	/**********************************/
	/*          Bullet Control        */
	void MakeBullet(int curTarget, TypeDame* typeDame, Color c, const b2Vec2& worldPos) override
	{
		auto e = enemyMgr.find(curTarget);
		if (e != enemyMgr.end())
		{
			const b2Vec2 enemyPos =  e->second->getBody().GetPosition();
			auto b = std::make_unique<Projectile>(box2DEngine, curTarget, worldPos + posOffSet, bulletSize);
			b->SetVelocity(enemyPos - worldPos);
			bulletMgr.emplace_back(std::move(b));
		}
	}
	/**********************************/


	/**********************************/
	/*         Enemy Control          */
	void MakeEnemy() override 
	{
		enemyMgr.emplace(indexEnemy, std::make_unique<Enemy>(box2DEngine, indexEnemy));
		indexEnemy++;
	}
	/**********************************/


	/**********************************/
	/*          Tower Control         */
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
		assert(t != towerMgr.end());
		t->second->Upgrade(typeDame);
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
	/**********************************/

private:
	int tileWidth;
	int tileHeight;
	b2Vec2 posOffSet;
	float timer = 0.0f;
	static constexpr float bulletSize = 0.2f;
	b2World& box2DEngine;
	IMediator* guiAndBoardMediator = nullptr;
	Border border;
	std::unordered_map<int, std::unique_ptr<Tower>> towerMgr;
	std::unordered_map<int, std::unique_ptr<Enemy>> enemyMgr;
	std::vector<std::unique_ptr<Projectile>> bulletMgr;
	int indexTower;
	int indexEnemy;
};