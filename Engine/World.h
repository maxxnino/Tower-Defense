#pragma once
#include <unordered_map>
#include <memory>
#include <assert.h>
#include <limits>
#include "ChiliUtil.h"
#include "Box2D/Box2D.h"
#include "IWorldMediator.h"
#include "IComponent.h"
#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"
#include "LineWall.h"
#include "Base.h"
#include "Gold.h"
class World : public IWorldMediator, public IComponent
{
public:
	World(b2World& box2DEngine, int tileWidth, int tileHeight)
		:
		box2DEngine(box2DEngine),
		border(box2DEngine),
		base(box2DEngine, {18.0f,0.0f}, {2,4}),
		gold(200),
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
		base.Draw(gfx);
		for (auto& b : bulletMgr)
		{
			b->Draw(gfx);
		}
		for (auto& b : noTargetBullet)
		{
			b->Draw(gfx);
		}
		for (auto& e : explosionMgr)
		{
			e->DrawAlpha(gfx);
		}
		
		
	}
	void Update(float dt)
	{
		std::for_each(towerMgr.begin(), towerMgr.end(), [dt,this](auto& t) {t.second->Update(dt); });
		std::for_each(enemyMgr.begin(), enemyMgr.end(), [dt,this](auto& e) {e.second->Update(dt); });
		for (int i = 0; i < bulletMgr.size();)
		{
			auto enemy = enemyMgr.find(bulletMgr[i]->GetEnemyID());
			if (enemy != enemyMgr.end())
			{
				bulletMgr[i]->SetVelocity(enemy->second->getBody().GetPosition() - bulletMgr[i]->getBody().GetPosition());
				i++;
			}
			else
			{
				std::swap(bulletMgr[i], bulletMgr.back());
				noTargetBullet.emplace_back(std::move(bulletMgr.back()));
				bulletMgr.pop_back();
			}
		}
		timer += dt;
		if (timer >= 1.5f)
		{
			timer = 0.0f;
			MakeEnemy();
		}
	}
	void CleanWorld(float dt)
	{
		//update and remove explosion effect
		for (int i = 0; i < explosionMgr.size();)
		{
			if (explosionMgr[i]->Update(dt))
			{
				std::swap(explosionMgr[i], explosionMgr.back());
				explosionMgr.pop_back();
			}
			else
			{
				i++;
			}
		}
		//clear dead bullet
		for (int i = 0; i < bulletMgr.size();)
		{
			if (bulletMgr[i]->isRemove())
			{
				explosionMgr.emplace_back(std::make_unique<OnetimeAnimation>(bulletMgr[i]->getElement()->GetExplosionAnimation(), bulletMgr[i]->GetPos()));
				std::swap(bulletMgr[i], bulletMgr.back());
				bulletMgr.pop_back();
			}
			else
			{
				bulletMgr[i]->Update(dt);
				i++;
			}
		}
		//clear dead enemy
		for (auto e = enemyMgr.begin(); e != enemyMgr.end();)
		{
			if (e->second->isRemove())
			{
				gold.AddGold(e->second->GetGold());
				e = enemyMgr.erase(e);
			}
			else if (e->second->IsReachtBase())
			{
				e = enemyMgr.erase(e);
			}
			else
			{
				e++;
			}
		}
		//clear no target dead bullet
		for (int i = 0; i < noTargetBullet.size();)
		{
			if (noTargetBullet[i]->isRemove())
			{
				std::swap(noTargetBullet[i], noTargetBullet.back());
				noTargetBullet.pop_back();
			}
			else
			{
				if (noTargetBullet[i]->CooldownToDead(dt))
				{
					std::swap(noTargetBullet[i], noTargetBullet.back());
					noTargetBullet.pop_back();
				}
				else
				{
					noTargetBullet[i]->Update(dt);
					i++;
				}
			}
		}
	}
	/**********************************/


	/**********************************/
	/*          Bullet Control        */
	void MakeBullet(int curTarget, Element* element, Color c, const b2Vec2& worldPos) override
	{
		auto e = enemyMgr.find(curTarget);
		if (e != enemyMgr.end())
		{
			const b2Vec2 enemyPos =  e->second->getBody().GetPosition();
			const b2Vec2 dir = enemyPos - worldPos;
			auto b = std::make_unique<Projectile>(box2DEngine, element, curTarget, worldPos + posOffSet, bulletSize);
			b->SetVelocity(dir);
			bulletMgr.emplace_back(std::move(b));
		}
	}
	/**********************************/


	/**********************************/
	/*         Enemy Control          */
	void MakeEnemy() override 
	{
		enemyMgr.emplace(indexEnemy, std::make_unique<Enemy>(box2DEngine, indexEnemy, 1.5f));
		if (indexEnemy > 10000)
		{
			indexEnemy = 0;
		}
		else
		{
			indexEnemy++;
		}
	}
	/**********************************/


	/**********************************/
	/*          Gold Control         */
	int GetGold() const
	{
		return gold.GetGold();
	}
	bool CanAffordTower(const MouseGame& mouseGame) const
	{
		return gold.GetGold() >= mouseGame.GetGold();
	}
	/**********************************/
	/**********************************/
	/*          Tower Control         */
	int MakeTower(Element* element, Color c, const b2Vec2& worldPos, float size = 1.0f) override
	{
		gold.RemoveGold(element->GetGold());
		auto tower = std::make_unique<Tower>(box2DEngine, element, c, worldPos, size);
		tower->AddMediator(this);
		towerMgr.emplace(indexTower, std::move(tower));
		indexTower++;
		return indexTower - 1;
	}
	void SellTower(int curTowerIndex) 
	{
		assert(curTowerIndex >= 0);
		assert(towerMgr.find(curTowerIndex) != towerMgr.end());
		auto t = towerMgr.find(curTowerIndex);
		gold.AddGold(int((float)(t->second->GetGold()) * sellRate + 0.5f));
		t->second->MarkDead();
		towerMgr.erase(curTowerIndex);
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
	void UpgradeTower(Element* element, int towerIndex) override
	{
		auto t = towerMgr.find(towerIndex);
		assert(t != towerMgr.end());
		auto newElement = guiAndBoardMediator->GetMouseGame()->MakeElement(t->second->getCurElement(), element);
		t->second->Upgrade(newElement);
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
	static constexpr float bulletSize = 0.3f;
	static constexpr float sellRate = 0.66667f;
	b2World& box2DEngine;
	IMediator* guiAndBoardMediator = nullptr;
	Gold gold;
	Border border;
	Base base;
	std::unordered_map<int, std::unique_ptr<Tower>> towerMgr;
	std::unordered_map<int, std::unique_ptr<Enemy>> enemyMgr;
	std::vector<std::unique_ptr<Projectile>> bulletMgr;
	std::vector<std::unique_ptr<Projectile>> noTargetBullet;
	std::vector<std::unique_ptr<OnetimeAnimation>> explosionMgr;
	int indexTower;
	int indexEnemy;
};