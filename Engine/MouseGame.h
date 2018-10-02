#pragma once
#include "Element.h"
#include "GameSettings.h"
enum MouseState
{
	None,
	BuildTower,
	SellTower,
	SwapTower,
	BuildEntity
};
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
		state = MouseState::None;
	}
	inline void ChangeToFire() noexcept
	{
		element = &fire;
		state = MouseState::BuildTower;
	}
	inline void ChangeToIce() noexcept
	{
		element = &water;
		state = MouseState::BuildTower;
	}
	inline void ChangeToLighting() noexcept
	{
		element = &nature;
		state = MouseState::BuildTower;
	}
	const std::shared_ptr<Surface> GetFireSurface()
	{
		return fire.GetElementSurface();
	}
	const std::shared_ptr<Surface> GetWaterSurface()
	{
		return water.GetElementSurface();
	}
	const std::shared_ptr<Surface> GetNatureSurface()
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
	bool IsEmptyCommand() const
	{
		return element == nullptr;
	}
	MouseState GetMouseState() const
	{
		return state;
	}
	void ChangeState(MouseState newState)
	{
		state = newState;
	}
	void SetPos(const VecI& newPos)
	{
		pos = newPos;
	}
	void Draw(Graphics& gfx)
	{
		switch (state)
		{
		case None:
			break;
		case BuildTower:
			//gfx.DrawSprite(pos.x, pos.y, *element->GetElementSurface(), SpriteEffect::Ghost(Colors::Magenta));
			element->GetTowerAnimation()->DrawGhost(pos, gfx, 0);
			break;
		case DeleteTower:
			break;
		case SwapTower:
			break;
		case DropItem:
			break;
		default:
			break;
		}
	}
private:
	Element* element = nullptr;
	VecI pos = { 0,0 };
	MouseState state = MouseState::None;
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

	//projectile animation data
	SharedAnimationData pro01 = { 0,0,30,30,2, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_01_30_30_2.png"), animationSpeed, Colors::Black };
	SharedAnimationData pro02 = { 30,0,30,30,8, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_02_30_30_9.png"), animationSpeed, Colors::Black };
	SharedAnimationData pro03 = { 0,0,30,30,2, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_03_30_30_14.png"), animationSpeed, Colors::Black };
	SharedAnimationData pro04 = { 0,0,30,30,8, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_04_30_30_8.png"), animationSpeed, Colors::Black };
	SharedAnimationData pro05 = { 0,0,30,30,4, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_05_30_30_4.png"), animationSpeed, Colors::Black };
	SharedAnimationData pro06 = { 0,0,30,30,4, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_06_30_30_4.png"), animationSpeed, Colors::Black };
	SharedAnimationData pro07 = { 0,0,30,30,4, Codex<Surface>::Retrieve(L"Images\\Projectile\\pm_pro_07_30_30_4.png"), animationSpeed, Colors::Black };


	Element def = { Element::Type::Fire, 1, 1, 1, Colors::Magenta, &towerAni01, &pro01};

	//lv01
	Element fire = { Element::Type::Fire, 1, 1,1,Colors::Red, &towerAni01, &pro01 };
	Element water = { Element::Type::Water, 1, 1,1,Colors::Blue, &towerAni02, &pro02 };
	Element nature = { Element::Type::Nature, 1, 1,1,Colors::Green, &towerAni03, &pro03 };

	//lv02
	Element fireFire = { Element::Type::Fire + Element::Type::Fire, 2, 1, 1, Colors::Magenta, &towerAni04, &pro06 };
	Element fireWater = { Element::Type::Fire + Element::Type::Water, 2, 1, 1, Colors::Magenta, &towerAni05, &pro05};
	Element fireNature = { Element::Type::Fire + Element::Type::Nature, 2, 1, 1, Colors::Magenta, &towerAni06, &pro07};
	Element waterWater = { Element::Type::Water + Element::Type::Water, 2, 1, 1, Colors::Magenta, &towerAni07, &pro04};
	Element waterNature = { Element::Type::Water + Element::Type::Nature, 2, 1, 1, Colors::Magenta, &towerAni08, &pro02};
	Element natureNature = { Element::Type::Nature + Element::Type::Nature, 2, 1, 1, Colors::Magenta, &towerAni09, &pro03};
};