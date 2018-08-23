#pragma once
#include <unordered_set>
#include "rect.h"
#include "graphics.h"
class tile
{
public:
	void additem(std::shared_ptr<igui> sub)
	{
		items.emplace_back(sub);
	}
	void awake()
	{
		c = colors::red;
	}
	void sleep()
	{
		c = colors::blue;
	}
	void draw(graphics& gfx, veci pos,int width, int height) const
	{
		gfx.drawrectdim(pos + veci(2, 2), width - 2, height - 2, c);
	}
private:
	std::vector<std::shared_ptr<igui>> items;
	color c = colors::blue;
};