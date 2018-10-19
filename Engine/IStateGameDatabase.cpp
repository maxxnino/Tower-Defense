#include "IStateGameDatabase.h"
#include "GuiGameDatabase.h"
#include "IMediator.h"

void IStateNormal::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	database->GetMediator().OpenUpgradeMenu(towerIndex);
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

void StateHoldDirGui::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	database->GetMediator().SetDirectionDG(mouseWorldPos);
}

bool StateHoldDirGui::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().SetDirectionDG(mouseWorldPos);
	return false;
}

bool StateHoldDirGui::UpdateNoBuildTile(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().SetDirectionDG(mouseWorldPos);
	return false;
}

void StateBuildMode::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	buildStategy->UpdateHaveTower(database, worldTilePos, trackingTile, mouseWorldPos, towerIndex);
}

bool StateBuildMode::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	return buildStategy->UpdateNoTower(database, worldTilePos, mouseWorldPos);
}

bool StateBuildMode::UpdateNoBuildTile(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	return buildStategy->UpdateNoBuildTile(database, worldTilePos, mouseWorldPos);
}

void StateBuildMode::Draw(const GuiGameDatabase * database, Graphics & gfx, const VecI & drawPos) const
{
	buildStategy->Draw(database, gfx, drawPos);
}
