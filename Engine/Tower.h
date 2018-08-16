#pragma once
#include "Colors.h"
#include <memory>
#include <assert.h>
class Tower
{
public:
	Tower(Color c)
		:
		c(c)
	{}
	const Color& GetColor() const
	{
		return c;
	}
	std::shared_ptr<Tower> Upgrade(int typeID);
private:
	Color c;
};

class FireTower : public Tower
{
public:
	FireTower()
		:
		Tower(Colors::MakeRGB(255u,80u,0u))
	{}
};

class WaterTower : public Tower
{
public:
	WaterTower()
		:
		Tower(Colors::MakeRGB(0u, 200u, 255u))
	{}
};

class NatureTower : public Tower
{
public:
	NatureTower()
		:
		Tower(Colors::MakeRGB(99u, 191u, 97u))
	{}
};