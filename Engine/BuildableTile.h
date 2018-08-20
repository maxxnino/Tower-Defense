#pragma once
#include "TileGame.h"

class BuildableTile : public TileGame
{
public:
	void Draw(Graphics& gfx, VecI pos, int width, int height, IObervable* obs) const override
	{
		if (isAwake)
		{
			auto typeDame = static_cast<MouseState*>(obs)->typeDame;
			if (typeDame == nullptr)
			{
				if (myTower != nullptr)
				{
					gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, myTower->GetColor());
				}
				else
				{
					gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
				}
			}
			else
			{
				gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, typeDame->getColor());
			}
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
		if (newType == nullptr)
		{
			if (myTower != nullptr)
			{
				Notify(this);
			}
		}
		else
		{
			if (myTower == nullptr)
			{
				myTower = std::make_shared<Tower>(Colors::Red);
				myTower->Upgrade(newType);
			}
		}
	}
	void OnNotify(Observer* userData) override
	{
		myTower->Upgrade(static_cast<Button*>(userData)->getData());
	}
	void AddEntity(std::shared_ptr<Tower> tower) override
	{
		myTower = tower;
	}
private:
	static constexpr Color c = Colors::Gray;
	std::shared_ptr<Tower> myTower;
};