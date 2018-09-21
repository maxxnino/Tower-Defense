#pragma once
#include "TileGame.h"
class BuildableTile : public TileGame
{
public:
	BuildableTile(VecI pos,int tileIndex, const std::shared_ptr<Surface> surf)
		:
		pos(pos),
		tileIndex(tileIndex),
		surf(surf)
	{}
	void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept override
	{
		//gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, defaultColor);
		gfx.DrawSprite(pos.x, pos.y, *surf, SpriteEffect::Copy{});
	}
	void MouseClick(const VecI& mousePos, IMediator* mediator) override
	{
		auto element = mediator->GetMouseGame()->getElement();
		if (element)
		{
			if (towerIndex == -1)
			{
				//view world object
				if (mediator->CanAffordTower())
				{
					BuildTower(element, mediator);
				}
				else
				{
					//view menumanager warning text
					mediator->ActiveWarningText(0);
				}
			}
			else
			{
				//view menumanager warning text
				mediator->ActiveWarningText(1);
			}
		}
		else
		{
			if (towerIndex != -1)
			{
				//nothing in mouse, and this tile have tower, clicked for open upgrade menu from Menumanager
				mediator->OpenUpgradeMenu(towerIndex, tileIndex);
			}
		}
	}
	void RemoveTowerIndex() override
	{
		towerIndex = -1;
	}
	void BuildTower(Element* type, IMediator* mediator)
	{
		assert(towerIndex == -1);
		b2Vec2 worldPos = b2Vec2((float32)(pos.x - Graphics::offSetX) / (float32)Graphics::scalePixel, (float32)(Graphics::offSetY - pos.y) / (float32)Graphics::scalePixel);
		float size = 10.0f;
		towerIndex = mediator->MakeTower(type, type->getColor(), worldPos, size);
	}
	int GetTileData() const override
	{
		return 1;
	}
private:
	static constexpr Color defaultColor = Colors::Gray;
	std::shared_ptr<Surface> surf;
	int towerIndex = -1;
	const int tileIndex;
	VecI pos;
};