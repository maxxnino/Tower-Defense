#include "IStateGameDatabase.h"
#include "GuiGameDatabase.h"
#include "IMediator.h"



void IStateGameDatabase::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	database->GetMediator().OpenUpgradeMenu(towerIndex);
}

void StateBuildTower::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	database->GetMediator().ActiveWarningText(1);
}

bool StateBuildTower::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().MakeTower(worldTilePos);
	return false;
}

void StateBuildTower::Draw(const GuiGameDatabase * database, Graphics & gfx, const VecI& drawPos) const
{
	database->getElement()->GetTowerAnimation()->DrawGhost(drawPos, gfx, 0);
}

void StateSellTower::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	database->GetMediator().DeleteTower(towerIndex);
}

bool StateSellTower::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().ActiveWarningText(2);
	return false;
}

void StateSellTower::Draw(const GuiGameDatabase * database, Graphics & gfx, const VecI& drawPos) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, *database->GetSellTowerSurf(), SpriteEffect::AlphaBlendBakedAndGhost());
}

void StateSwapTower::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
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
			database->GetMediator().DoSwapTower(swapSlot01.first, swapSlot01.second, trackingTile, towerIndex);
		}
		else
		{
			database->GetMediator().ActiveWarningText(2);
		}
	}
}

bool StateSwapTower::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().ActiveWarningText(2);
	return false;
}

void StateSwapTower::Draw(const GuiGameDatabase * database, Graphics & gfx, const VecI& drawPos) const
{
	if (swapSlot01.second != -1)
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, *database->GetSwapTowerSurf(), SpriteEffect::AlphaBlendBakedAndGhost());
	}
	else
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, *database->GetSwapTowerSurf(), SpriteEffect::AlphaBlendBakedAndGhost());
	}
}

void StateBuildDirGui::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	database->GetMediator().MakeDirectionGuiding(mouseWorldPos);
}

bool StateBuildDirGui::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().MakeDirectionGuiding(mouseWorldPos);
	return false;
}

bool StateBuildDirGui::UpdateNoBuildTile(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().MakeDirectionGuiding(mouseWorldPos);
	return false;
}

void StateSelectDirGui::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	if (database->GetMediator().SelectDirGuiding(mouseWorldPos))
	{
		database->ChangeHoldDirGui();
	}
}

bool StateSelectDirGui::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	if (database->GetMediator().SelectDirGuiding(mouseWorldPos))
	{
		database->ChangeHoldDirGui();
		return false;
	}
	return true;
}

bool StateSelectDirGui::UpdateNoBuildTile(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	if (database->GetMediator().SelectDirGuiding(mouseWorldPos))
	{
		database->ChangeHoldDirGui();
		return false;
	}
	return true;
}

void HoldDirGui::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	database->GetMediator().SetDirectionDG(mouseWorldPos);
}

bool HoldDirGui::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().SetDirectionDG(mouseWorldPos);
	return false;
}

bool HoldDirGui::UpdateNoBuildTile(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().SetDirectionDG(mouseWorldPos);
	return false;
}