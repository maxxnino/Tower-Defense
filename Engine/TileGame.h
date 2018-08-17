#pragma once
#include <vector>
#include <memory>
#include "Vec2.h"
#include "Graphics.h"
#include "Tower.h"
#include "Listener.h"
class TileGame
{
public:
	virtual void MouseClick(const VecI& mousePos, Listener* listener) = 0;
	void MouseMove(const VecI& mousePos)
	{
		/*for (auto i : items)
		{
			if (i->GetRect().isContaint(mousePos))
			{
				i->MouseIn();
			}
			else
			{
				i->MouseLeave();
			}
		}*/
	}
	virtual void AddEntity(std::shared_ptr<Tower>) = 0;
	void Awake()
	{
		isAwake = true;
	}
	void Sleep()
	{
		isAwake = false;
	}
	virtual void Upgrade(int typeID) = 0;
	virtual void Draw(Graphics& gfx, VecI pos, int width, int height) const = 0;
	/*{
		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
	}*/
protected:
	bool isAwake = false;
};