#pragma once
#include "TileGame.h"

class BuildableTile : public TileGame
{
public:
	void Draw(Graphics& gfx, VecI pos, int width, int height) const override
	{
		if (isAwake)
		{
			gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, Colors::Blue);
		}
		else
		{
			if (myTower)
			{
				gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, myTower->GetColor());
			}
			else
			{
				gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
			}
		}
	}
	void MouseClick(const VecI& mousePos,IObervable* obs) override
	{
		auto newType = static_cast<MouseState*>(obs)->typeDame;
		if (myTower == nullptr)
		{
			myTower = std::make_shared<Tower>(Colors::Red);
		}
		else
		{
			if (newType == nullptr)
			{
				Notify(this);
			}
		}
	}
	void OnNotify(void* userData) override
	{
		auto data = static_cast<Button*>(userData)->getData();
		myTower->Upgrade(static_cast<TypeDame*>(data));
	}
	void AddEntity(std::shared_ptr<Tower> tower) override
	{
		myTower = tower;
	}
private:
	static constexpr Color c = Colors::Gray;
	std::shared_ptr<Tower> myTower;
};