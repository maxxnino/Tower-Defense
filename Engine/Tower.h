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
	virtual std::shared_ptr<Tower> Upgrade(int typeID) = 0;
private:
	Color c;
};