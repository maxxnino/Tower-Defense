#pragma once
#include "Element.h"
#include "GameSettings.h"
class MouseGame
{
public:
	MouseGame()
		:
		animationSpeed(GameSettings::Get().GetData("[Animation Speed]"))
	{
		fire.SetElementSurface(Codex<Surface>::Retrieve(L"Images\\GUI\\pm_fire_50_50.png"));
		water.SetElementSurface(Codex<Surface>::Retrieve(L"Images\\GUI\\pm_water_50_50.png"));
		nature.SetElementSurface(Codex<Surface>::Retrieve(L"Images\\GUI\\pm_nature_50_50.png"));
		//lv01
		factory.emplace(fire.getType(), &fire);
		factory.emplace(water.getType(), &water);
		factory.emplace(nature.getType(), &nature);

		//lv02
		factory.emplace(fireFire.getType(), &fireFire);
		factory.emplace(fireWater.getType(), &fireWater);
		factory.emplace(fireNature.getType(), &fireNature);
		factory.emplace(waterWater.getType(), &waterWater);
		factory.emplace(waterNature.getType(), &waterNature);
		factory.emplace(natureNature.getType(), &natureNature);
	}
	Element* getElement()
	{
		return element;
	}
	inline void Clear() noexcept
	{
		element = nullptr;
	}
	inline void ChangeToFire() noexcept
	{
		element = &fire;
	}
	inline void ChangeToIce() noexcept
	{
		element = &water;
	}
	inline void ChangeToLighting() noexcept
	{
		element = &nature;
	}
	const Surface* GetFireSurface()
	{
		return fire.GetElementSurface();
	}
	const Surface* GetWaterSurface()
	{
		return water.GetElementSurface();
	}
	const Surface* GetNatureSurface()
	{
		return nature.GetElementSurface();
	}
	Color GetFireColor() noexcept
	{
		return fire.getColor();
	}
	Color GetIceColor() noexcept
	{
		return water.getColor();
	}
	Color GetLightingColor() noexcept
	{
		return nature.getColor();
	}
	inline int GetGold() const
	{
		assert(element);
		return element->GetGold();
	}
	Element* MakeElement(Element* a, Element* b)
	{
		const int type = a->getType() + b->getType();
		auto it = factory.find(type);
		if (it != factory.end())
		{
			return it->second;
		}
		else
		{
			assert(false);
			return &def;
		}
	}
private:
	Element* element = nullptr;
	float animationSpeed;
	std::unordered_map<int, Element*> factory;

	//tower animation data pm_tower_lv09_40_40_6 pm_tower_lv03_40_40_12
	SharedAnimationData towerAni01 = { 0,0,40,40,9, Codex<Surface>::Retrieve(L"Images\\Tower\\pm_tower_lv01_40_40_9.png"), animationSpeed, Colors::Black };
	SharedAnimationData towerAni02 = { 0,0,40,40,11, Codex<Surface>::Retrieve(L"Images\\Tower\\pm_tower_lv02_40_40_11.png"), animationSpeed, Colors::Black };
	SharedAnimationData towerAni03 = { 0,0,40,40,6, Codex<Surface>::Retrieve(L"Images\\Tower\\pm_tower_lv03_40_40_6.png"), animationSpeed, Colors::Black };
	SharedAnimationData towerAni04 = { 0,0,40,40,12, Codex<Surface>::Retrieve(L"Images\\Tower\\pm_tower_lv04_40_40_12.png"), animationSpeed, Colors::Black };
	SharedAnimationData towerAni05 = { 0,0,40,40,5, Codex<Surface>::Retrieve(L"Images\\Tower\\pm_tower_lv05_40_40_5.png"), animationSpeed, Colors::Black };
	SharedAnimationData towerAni06 = { 0,0,40,40,5, Codex<Surface>::Retrieve(L"Images\\Tower\\pm_tower_lv06_40_40_5.png"), animationSpeed, Colors::Black };
	SharedAnimationData towerAni07 = { 0,0,40,40,12, Codex<Surface>::Retrieve(L"Images\\Tower\\pm_tower_lv07_40_40_12.png"), animationSpeed, Colors::Black };
	SharedAnimationData towerAni08 = { 0,0,40,40,8, Codex<Surface>::Retrieve(L"Images\\Tower\\pm_tower_lv08_40_40_8.png"), animationSpeed, Colors::Black };
	SharedAnimationData towerAni09 = { 0,0,40,40,6, Codex<Surface>::Retrieve(L"Images\\Tower\\pm_tower_lv09_40_40_6.png"), animationSpeed, Colors::Black };

	//explosion animation pm_explosion_02_40_40_5
	SharedAnimationData explosion01 = { 0,0,40,40,19, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_01_40_40_19.png"), 0.3f * animationSpeed, Colors::Black };
	SharedAnimationData explosion02 = { 0,0,40,40,19, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_02_40_40_19.png"), 0.3f * animationSpeed, Colors::Black };
	SharedAnimationData explosion03 = { 0,0,40,40,17, Codex<Surface>::Retrieve(L"Images\\Explosion\\pm_explosion_03_40_40_17.png"), 0.35f * animationSpeed, Colors::Black };

	//projectile animation data
	SharedAnimationData pro01 = { 0,0,30,30,2, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_30_30_2.png"), animationSpeed, Colors::Black };
	SharedAnimationData pro02 = { 30,0,30,30,8, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_30_30_9.png"), animationSpeed, Colors::Black };
	SharedAnimationData pro03 = { 0,0,30,30,2, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_30_30_14.png"), animationSpeed, Colors::Black };

	Element def = { Element::Type::Fire, 1, 1, 1, Colors::Magenta, &towerAni01, &pro01, &explosion01 };

	//lv01
	Element fire = { Element::Type::Fire, 1, 1,1,Colors::Red, &towerAni01, &pro01, &explosion01 };
	Element water = { Element::Type::Water, 1, 1,1,Colors::Blue, &towerAni02, &pro02, &explosion02 };
	Element nature = { Element::Type::Nature, 1, 1,1,Colors::Green, &towerAni03, &pro03, &explosion03 };

	//lv02
	Element fireFire = { Element::Type::Fire + Element::Type::Fire, 2, 1, 1, Colors::Magenta, &towerAni04, &pro01, &explosion01 };
	Element fireWater = { Element::Type::Fire + Element::Type::Water, 2, 1, 1, Colors::Magenta, &towerAni05, &pro02, &explosion02 };
	Element fireNature = { Element::Type::Fire + Element::Type::Nature, 2, 1, 1, Colors::Magenta, &towerAni06, &pro03, &explosion03 };
	Element waterWater = { Element::Type::Water + Element::Type::Water, 2, 1, 1, Colors::Magenta, &towerAni07, &pro01, &explosion01 };
	Element waterNature = { Element::Type::Water + Element::Type::Nature, 2, 1, 1, Colors::Magenta, &towerAni08, &pro02, &explosion02 };
	Element natureNature = { Element::Type::Nature + Element::Type::Nature, 2, 1, 1, Colors::Magenta, &towerAni09, &pro03, &explosion03 };
};