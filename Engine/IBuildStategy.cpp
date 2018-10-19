#include "IBuildStategy.h"
#include "GuiGameDatabase.h"
#include "IMediator.h"

void BuildTowerStategy::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	database->GetMediator().ActiveWarningText(1);
}

bool BuildTowerStategy::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().MakeTower(worldTilePos);
	return false;
}

void BuildTowerStategy::Draw(const GuiGameDatabase * database, Graphics & gfx, const VecI & drawPos) const
{
	database->getElement()->GetTowerAnimation()->DrawGhost(drawPos, gfx, 0);
}

void BuildDirGuiStategy::UpdateHaveTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, int towerIndex)
{
	database->GetMediator().MakeDirectionGuiding(mouseWorldPos);
}

bool BuildDirGuiStategy::UpdateNoTower(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().MakeDirectionGuiding(mouseWorldPos);
	return false;
}

bool BuildDirGuiStategy::UpdateNoBuildTile(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	database->GetMediator().MakeDirectionGuiding(mouseWorldPos);
	return false;
}
