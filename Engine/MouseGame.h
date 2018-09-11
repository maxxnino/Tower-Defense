#pragma once
#include "Element.h"
class MouseGame
{
public:
	MouseGame()
	{
		fire.SetElementSurface(Codex<Surface>::Retrieve(L"Images\\pm_fire_50_50.png"));
		water.SetElementSurface(Codex<Surface>::Retrieve(L"Images\\pm_water_50_50.png"));
		nature.SetElementSurface(Codex<Surface>::Retrieve(L"Images\\pm_nature_50_50.png"));
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
	std::unordered_map<int, Element*> factory;
	Element def = { Element::Type::Fire, 1, 1, 1, Colors::Magenta, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_01.png") };

	//lv01
	Element fire = { Element::Type::Fire, 1, 1,1,Colors::Red,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_01.png") };
	Element water = { Element::Type::Water, 1, 1,1,Colors::Blue,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_02.png") };
	Element nature = { Element::Type::Nature, 1, 1,1,Colors::Green,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_03.png") };

	//lv02
	Element fireFire = { Element::Type::Fire + Element::Type::Fire, 2, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_01.png") };
	Element fireWater = { Element::Type::Fire + Element::Type::Water, 2, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_02.png") };
	Element fireNature = { Element::Type::Fire + Element::Type::Nature, 2, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_03.png") };
	Element waterWater = { Element::Type::Water + Element::Type::Water, 2, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_04.png") };
	Element waterNature = { Element::Type::Water + Element::Type::Nature, 2, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_05.png") };
	Element natureNature = { Element::Type::Nature + Element::Type::Nature, 2, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_06.png") };
};