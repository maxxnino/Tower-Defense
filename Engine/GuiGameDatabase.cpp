#include "GuiGameDatabase.h"
#include "IMediator.h"
void GuiGameDatabase::AddMediator(IMediator* mediator)
{
	this->mediator = mediator;
}

void GuiGameDatabase::Draw(Graphics & gfx, const Camera & cam) const
{
	const auto drawPos = cam.GetDrawPosition(pos);
	switch (state)
	{
	case None:
		break;
	case BuildTower:
		//gfx.DrawSprite(pos.x, pos.y, *element->GetElementSurface(), SpriteEffect::Ghost(Colors::Magenta));
		element->GetTowerAnimation()->DrawGhost(drawPos, gfx, 0);
		break;
	case SellTower:
		gfx.DrawSprite(drawPos.x, drawPos.y, *sellTowerSurf, SpriteEffect::AlphaBlendBakedAndGhost());
		break;
	case SwapTower:
		if (swapSlot01.second != -1)
		{
			gfx.DrawSprite(drawPos.x, drawPos.y, *swapTowerSurf, SpriteEffect::AlphaBlendBakedAndGhost());
		}
		else
		{
			gfx.DrawSprite(drawPos.x, drawPos.y, *swapTowerSurf, SpriteEffect::AlphaBlendBakedAndGhost());
		}
		break;
		/*case DropItem:
			break;
		default:
			break;*/
	}
}

void GuiGameDatabase::UpdateHaveTower(const b2Vec2& worldTilePos, const VecI& trackingTile, int towerIndex)
{
	switch (state)
	{
	case None:
		mediator->OpenUpgradeMenu(towerIndex);
		break;
	case BuildTower:
		mediator->ActiveWarningText(1);
		break;
	case SellTower:
		mediator->DeleteTower(towerIndex);
		break;
	case SwapTower:
		{
			if (swapSlot01.second == -1)
			{
				swapSlot01.first = trackingTile;
				swapSlot01.second = towerIndex;
			}
			else
			{
				if (swapSlot01.second != towerIndex)
				{
					mediator->DoSwapTower(swapSlot01.first, swapSlot01.second, trackingTile, towerIndex);
				}
				else
				{
					mediator->ActiveWarningText(2);
				}
			}
			break;
		}
	}
}

bool GuiGameDatabase::UpdateNoTower(const b2Vec2& worldTilePos)
{
	switch (state)
	{
	case None:
		return true;
	case BuildTower:
		mediator->MakeTower(worldTilePos);
		return false;
	case SellTower:
		mediator->ActiveWarningText(2);
		return false;
	case SwapTower:
		mediator->ActiveWarningText(2);
		return false;
	case BuildEntity:
		break;
	}
	return true;
}
