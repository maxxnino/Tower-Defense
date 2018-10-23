#include "IStateGameDatabase.h"
#include "GuiGameDatabase.h"
#include "IMediator.h"

void IStateNormal::Update(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType)
{
	if (tileType == TileType::HaveTower)
	{
		database->GetMediator().OpenUpgradeMenu();
	}
}

void StateSellTower::Draw(const GuiGameDatabase * database, Graphics & gfx, const VecI& drawPos) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, *database->GetSellTowerSurf(), SpriteEffect::AlphaBlendBakedAndGhost());
}

void StateSellTower::Update(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType)
{
	switch (tileType)
	{
	case None:
		database->GetMediator().ActiveWarningText(2);
		break;
	case Buildable:
		database->GetMediator().ActiveWarningText(2);
		break;
	case HaveTower:
		database->GetMediator().DeleteTower();
		break;
	}
}

void StateSwapTower::Draw(const GuiGameDatabase * database, Graphics & gfx, const VecI& drawPos) const
{
	/*if (swapSlot01.second != -1)
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, *database->GetSwapTowerSurf(), SpriteEffect::AlphaBlendBakedAndGhost());
	}
	else
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, *database->GetSwapTowerSurf(), SpriteEffect::AlphaBlendBakedAndGhost());
	}*/
}

void StateSwapTower::Update(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType)
{
	switch (tileType)
	{
	case None:
		database->GetMediator().ActiveWarningText(2);
		break;
	case Buildable:
		database->GetMediator().ActiveWarningText(2);
		break;
	case HaveTower:
		database->GetMediator().SwapTower(trackingTile);
		break;
	}
}

void StateSelectDirGui::Update(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType)
{
	if (database->GetMediator().SelectDirGuiding(mouseWorldPos))
	{
		database->ChangeHoldDirGui();
	}
}


void StateHoldDirGui::Update(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType)
{
	database->GetMediator().SetDirectionDG(mouseWorldPos);
}

void StateBuildTower::Draw(const GuiGameDatabase * database, Graphics & gfx, const VecI & drawPos) const
{
	database->getElement()->GetTowerAnimation()->DrawGhost(drawPos, gfx, 0);
}

void StateBuildTower::Update(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType)
{
	switch (tileType)
	{
	case Buildable:
		database->GetMediator().MakeTower(worldTilePos);
		break;
	case HaveTower:
		database->GetMediator().ActiveWarningText(1);
		break;
	}
}

void StateBuildGirGui::Draw(const GuiGameDatabase * database, Graphics & gfx, const VecI & drawPos) const
{
	gfx.DrawCircle(drawPos + VecI(20,20), 20, Colors::Magenta);
}

void StateBuildGirGui::Update(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType)
{
	database->GetMediator().MakeDirectionGuiding(worldTilePos + b2Vec2(1.0f, -1.0f));
}

void StateBuildBorder::Update(GuiGameDatabase * database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType)
{

}
