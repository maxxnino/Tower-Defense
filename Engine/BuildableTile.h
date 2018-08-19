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
	void Upgrade(int typeID) override
	{
		auto newTower = myTower->Upgrade(typeID);
		myTower = newTower;
	}
	void MouseClick(const VecI& mousePos,IObervable* obs) override
	{
		auto data = static_cast<MouseState*>(obs)->data;
		if (myTower == nullptr)
		{
			Upgrade(data);
		}
		else
		{
			if (data == 0)
			{
				Notify(this);
			}
			else
			{
				Upgrade(data);
			}
		}
	}
	void OnNotify(void* userData) override
	{
		auto data = static_cast<Button*>(userData)->getData();
		Upgrade(static_cast<Button*>(userData)->getData());
	}
	void AddEntity(std::shared_ptr<Tower> tower) override
	{
		myTower = tower;
	}
private:
	static constexpr Color c = Colors::Gray;
	std::shared_ptr<Tower> myTower;
};