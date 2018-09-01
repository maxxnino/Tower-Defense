#pragma once
#include "TileGame.h"
class BuildableTile : public TileGame
{
public:
	BuildableTile(VecI pos,int index)
		:
		pos(pos),
		index(index)
	{}
	void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept override
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
	void MouseClick(const VecI& mousePos, IMediator* mediator) override
	{
		auto typeDame = mediator->GetMouseGame()->getTypeDame();
		if (typeDame)
		{
			if (!myTower)
			{
				BuildTower(typeDame);
			}
			else
			{
				//Todo: show message can't build tower at here
			}
		}
		else
		{
			if (myTower)
			{
				//nothing in mouse, and this tile have tower, clicked for open upgrade menu from Menumanager
				mediator->OpenUpgradeMenu(index);
			}
		}
	}
	void AddEntity(std::shared_ptr<Tower> tower) override
	{
		myTower = tower;
	}
	void UpgradeTower(TypeDame* typeDame) override
	{
		myTower->Upgrade(typeDame);
	}
	void DeleteTower()
	{
		myTower.reset();
	}
	void BuildTower(TypeDame* type)
	{
		if (!myTower)
		{
			b2Vec2 worldPos = b2Vec2((float32)(pos.x - Graphics::offSetX) / (float32)Graphics::scalePixel, (float32)(Graphics::offSetY - pos.y) / (float32)Graphics::scalePixel);
			float size = 10.0f;
			myTower = std::make_shared<Tower>(Colors::Red, worldPos, size);
			myTower->Upgrade(type);
		}
	}
private:
	static constexpr Color c = Colors::Gray;
	std::shared_ptr<Tower> myTower;
	VecI pos;
	int index;
};