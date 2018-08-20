#pragma once
#include <vector>
#include <memory>
#include "Vec2.h"
#include "Graphics.h"
#include "Tower.h"
class TileGame : public Observer, public IObervable
{
public:
	virtual void MouseClick(const VecI& mousePos, IObervable* obs) = 0;
	void MouseMove(const VecI& mousePos)
	{
	}
	virtual void AddEntity(std::shared_ptr<Tower>) = 0;
	void OnNotify(void* userData) override {};
	void Awake()
	{
		isAwake = true;
	}
	void Sleep()
	{
		isAwake = false;
	}
	virtual void Draw(Graphics& gfx, VecI pos, int width, int height, IObervable* obs) const = 0;
	/*{
		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
	}*/
protected:
	bool isAwake = false;
};