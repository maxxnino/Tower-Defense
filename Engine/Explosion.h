#pragma once
#include <vector>
#include <memory>
#include <random>
#include "Codex.h"
#include "SharedAnimation.h"
#include "GameSettings.h"
class Explosion
{
public:
	Explosion()
	{
		explosionDatas.emplace_back(&explosion01);
		explosionDatas.emplace_back(&explosion02);
		explosionDatas.emplace_back(&explosion03);
	}
	template<class T>
	void AddExplosion(T& rng, const VecI& pos)
	{
		std::uniform_int_distribution<unsigned int> typeDist(0, (int)explosionDatas.size() - 1);
		explosionMgr.emplace_back(std::make_unique<OnetimeAnimation>(explosionDatas[typeDist(rng)], pos));
	}
	void Update(float dt)
	{
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
	}
	void Draw(Graphics& gfx)
	{
		for (auto& e : explosionMgr)
		{
			e->DrawAlpha(gfx);
		}
	}
private:
	//explosion animation pm_explosion_02_40_40_5
	const float animationSpeed = GameSettings::Get().GetData("[Animation Speed]");
	SharedAnimationData explosion01 = { 0,0,40,40,19, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_01_40_40_19.png"), 0.3f * animationSpeed, Colors::Black };
	SharedAnimationData explosion02 = { 0,0,40,40,19, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_02_40_40_19.png"), 0.3f * animationSpeed, Colors::Black };
	SharedAnimationData explosion03 = { 0,0,40,40,17, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_03_40_40_17.png"), 0.35f * animationSpeed, Colors::Black };
	std::vector<SharedAnimationData*> explosionDatas;
	std::vector<std::unique_ptr<OnetimeAnimation>> explosionMgr;
};