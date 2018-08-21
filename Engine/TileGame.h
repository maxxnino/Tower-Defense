#pragma once
#include <vector>
#include <memory>
#include "Vec2.h"
#include "Graphics.h"
#include "Tower.h"
#include "Observer.h"
class TileGame : public Observer, public IObervable
{
public:
	virtual void MouseClick(const VecI& mousePos, IObervable* obs) noexcept = 0;
	void MouseMove(const VecI& mousePos) noexcept
	{
	}
	virtual void AddEntity(std::shared_ptr<Tower>) = 0;
	void OnNotify(Observer* userData) override {};
	inline void Awake() noexcept
	{
		isAwake = true;
	}
	inline void Sleep() noexcept
	{
		isAwake = false;
	}
	virtual void Draw(Graphics& gfx, VecI pos, int width, int height, IObervable* obs) const noexcept = 0;
	/*{
		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
	}*/
protected:
	bool isAwake = false;
};