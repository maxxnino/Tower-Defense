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
		explosionDatas.emplace_back(&explosion04);
		explosionDatas.emplace_back(&explosion05);
		explosionDatas.emplace_back(&explosion06);
		explosionDatas.emplace_back(&explosion07);
	}
	template<class T>
	void AddExplosion(T& rng, const VecI& pos)
	{
		std::uniform_int_distribution<unsigned int> typeDist(0, (int)explosionDatas.size() - 1);
		if (typeDist(rng) < (unsigned int)(explosionDatas.size() - 1) / 2)
		{
			explosionMgr.emplace_back(std::make_unique<OnetimeAnimation>(explosionDatas[typeDist(rng)], pos, true));
		}
		else
		{
			explosionMgr.emplace_back(std::make_unique<OnetimeAnimation>(explosionDatas[typeDist(rng)], pos));
		}
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
	void Draw(Graphics& gfx, const VecI& camPos)
	{
		for (auto& e : explosionMgr)
		{
			e->DrawAlphaOffSet(gfx, camPos);
		}
	}
private:
	//explosion animation pm_explosion_02_40_40_5
	const float animationSpeed = GameSettings::Get().GetData("[Animation Speed]");
	SharedAnimationData explosion01 = { 0,0,40,40,19, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_01_40_40_19.png"), 0.5f * animationSpeed, Colors::Black };
	SharedAnimationData explosion02 = { 120,0,40,40,24, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_02_40_40_27.png"), 0.4f * animationSpeed, Colors::Black };
	SharedAnimationData explosion03 = { 0,0,40,40,17, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_03_40_40_17.png"), 0.5f * animationSpeed, Colors::Black };
	SharedAnimationData explosion04 = { 0,0,40,40,17, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_04_40_40_17.png"), 0.5f * animationSpeed, Colors::Black };
	SharedAnimationData explosion05 = { 0,0,40,40,24, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_05_40_40_24.png"), 0.5f * animationSpeed, Colors::Black };
	SharedAnimationData explosion06 = { 0,0,40,40,24, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_06_40_40_24.png"), 0.5f * animationSpeed, Colors::Black };
	SharedAnimationData explosion07 = { 0,0,40,40,24, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_07_40_40_24.png"), 0.6f * animationSpeed, Colors::Black };
	std::vector<SharedAnimationData*> explosionDatas;
	std::vector<std::unique_ptr<OnetimeAnimation>> explosionMgr;
};