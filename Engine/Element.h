#pragma once
#include "Projectile.h"
#include "Colors.h"
#include "Codex.h"
class Element
{
public:
	Element(float attackSpeedMultiply, float dameMultiply, Color c, const Surface* surf)
		:
		attackSpeedMultiply(attackSpeedMultiply),
		dameMultiply(dameMultiply),
		c(c),
		surf(surf)
	{}
	virtual float getDame() = 0;
	virtual float getAttackSpeed() = 0;
	virtual int GetGold() const = 0;
	virtual std::unique_ptr<Element> Clone() = 0;
	inline const Color& getColor() const noexcept
	{
		return c;
	}
	inline Color getColor() noexcept
	{
		return c;
	}
	const Surface* GetSurface()
	{
		return surf;
	}
protected:
	float baseAttackSpeed = 1.0f;
	int baseGold = 5;
	float baseDame = 10.0f;
	float attackSpeedMultiply;
	float dameMultiply;
	Color c;
	const Surface* surf;
};
class Fire : public Element
{
public:
	Fire()
		:
		Element(1.0f, 2.0f,Colors::Red, Codex<Surface>::Retrieve(L"Images\\pm_tower_01.png"))
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold - 3;
	}
	std::unique_ptr<Element> Clone() override
	{
		return std::make_unique<Fire>();
	}
};
class Ice : public Element
{
public:
	Ice()
		:
		Element(1.5f, 1.5f, Colors::Green, Codex<Surface>::Retrieve(L"Images\\pm_tower_02.png"))
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold - 2;
	}
	std::unique_ptr<Element> Clone() override
	{
		return std::make_unique<Ice>();
	}
};
class Lighting : public Element
{
public:
	Lighting()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_03.png"))
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold;
	}
	std::unique_ptr<Element> Clone() override
	{
		return std::make_unique<Lighting>();
	}
};
class FireIce : public Element
{
public:
	FireIce()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_03.png"))
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold;
	}
	std::unique_ptr<Element> Clone() override
	{
		return std::make_unique<FireIce>();
	}
};
class FireFire : public Element
{
public:
	FireFire()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_03.png"))
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold;
	}
	std::unique_ptr<Element> Clone() override
	{
		return std::make_unique<FireFire>();
	}
};
class IceIce : public Element
{
public:
	IceIce()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_03.png"))
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold;
	}
	std::unique_ptr<Element> Clone() override
	{
		return std::make_unique<IceIce>();
	}
};
class FireLight : public Element
{
public:
	FireLight()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_03.png"))
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold;
	}
	std::unique_ptr<Element> Clone() override
	{
		return std::make_unique<FireLight>();
	}
};
class IceLight : public Element
{
public:
	IceLight()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_03.png"))
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold;
	}
	std::unique_ptr<Element> Clone() override
	{
		return std::make_unique<IceLight>();
	}
};
class LightLight : public Element
{
public:
	LightLight()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_03.png"))
	{}
	float getDame() override
	{
		return baseAttackSpeed * dameMultiply;
	}
	float getAttackSpeed() override
	{
		return baseAttackSpeed * attackSpeedMultiply;
	}
	int GetGold() const override
	{
		return baseGold;
	}
	std::unique_ptr<Element> Clone() override
	{
		return std::make_unique<LightLight>();
	}
};