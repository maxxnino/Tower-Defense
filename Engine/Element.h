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
	virtual int GetLv() { return 0; };
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
		Element(1.0f, 2.0f,Colors::Red, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_01.png"))
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
	int GetLv() override { return lv; };
private:
	static constexpr int lv = 1;
};
class Ice : public Element
{
public:
	Ice()
		:
		Element(1.5f, 1.5f, Colors::Green, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_02.png"))
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
	int GetLv() override { return lv; };
private:
	static constexpr int lv = 1;
};
class Lighting : public Element
{
public:
	Lighting()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv01_03.png"))
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
	int GetLv() override { return lv; };
private:
	static constexpr int lv = 1;
};
class FireIce : public Element
{
public:
	FireIce()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_01.png"))
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
	int GetLv() override { return lv; };
private:
	static constexpr int lv = 2;
};
class FireFire : public Element
{
public:
	FireFire()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_02.png"))
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
	int GetLv() override { return lv; };
private:
	static constexpr int lv = 2;
};
class IceIce : public Element
{
public:
	IceIce()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_03.png"))
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
	int GetLv() override { return lv; };
private:
	static constexpr int lv = 2;
};
class FireLight : public Element
{
public:
	FireLight()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_04.png"))
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
	int GetLv() override { return lv; };
private:
	static constexpr int lv = 1;
};
class IceLight : public Element
{
public:
	IceLight()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_05.png"))
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
	int GetLv() override { return lv; };
private:
	static constexpr int lv = 2;
};
class LightLight : public Element
{
public:
	LightLight()
		:
		Element(0.5f, 0.75f, Colors::Blue, Codex<Surface>::Retrieve(L"Images\\pm_tower_lv02_06.png"))
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
	int GetLv() override { return lv; };
private:
	static constexpr int lv = 2;
};