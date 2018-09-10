#pragma once
#include "Element.h"
#include "Codex.h"
#include "Surface.h"
#include <unordered_map>
#include <assert.h>
class ElementFactory
{
public:
	ElementFactory()
	{
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
	Element* MakeElement(int type)
	{
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
	std::unordered_map<int, Element*> factory;
	Element def = { Element::Type::Fire, 1, 1, Colors::Magenta, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_01.png") };

	//lv01
	Element fire = { Element::Type::Fire, 1,1,Colors::Red,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_01.png") };
	Element water = { Element::Type::Water, 1,1,Colors::Blue,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_02.png") };
	Element nature = { Element::Type::Nature, 1,1,Colors::Green,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_03.png") };

	//lv02
	Element fireFire = { Element::Type::Fire + Element::Type::Fire, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_01.png") };
	Element fireWater = { Element::Type::Fire + Element::Type::Water, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_02.png") };
	Element fireNature = { Element::Type::Fire + Element::Type::Nature, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_03.png") };
	Element waterWater = { Element::Type::Water + Element::Type::Water, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_04.png") };
	Element waterNature = { Element::Type::Water + Element::Type::Nature, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_05.png") };
	Element natureNature = { Element::Type::Nature + Element::Type::Nature, 1,1,Colors::Magenta,Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_06.png") };
};