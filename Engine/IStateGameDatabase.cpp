#include "IStateGameDatabase.h"
#include "GuiGameDatabase.h"
#include "IMediator.h"

void IStateNormal::OnClick(GuiGameDatabase * database)
{
	if (tileType == TileType::HaveTower)
	{
		database->GetMediator().OpenUpgradeMenu();
	}
}

void StateSellTower::Draw(const GuiGameDatabase * database, Graphics & gfx, const Camera& cam) const
{
	const auto drawPos = cam.GetDrawPosition(worldTilePos);
	gfx.DrawSprite(drawPos.x, drawPos.y, *database->GetSellTowerSurf(), SpriteEffect::AlphaBlendBakedAndGhost());
}

void StateSellTower::OnClick(GuiGameDatabase * database)
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

void StateSwapTower::Draw(const GuiGameDatabase * database, Graphics & gfx, const Camera& cam) const
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

void StateSwapTower::OnClick(GuiGameDatabase * database)
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

void StateSelectDirGui::OnClick(GuiGameDatabase * database)
{
	if (database->GetMediator().SelectDirGuiding(mouseWorldPos))
	{
		database->ChangeHoldDirGui();
	}
}


void StateHoldDirGui::OnClick(GuiGameDatabase * database)
{
	database->GetMediator().SetDirectionDG(mouseWorldPos);
}

void StateBuildTower::Draw(const GuiGameDatabase * database, Graphics & gfx, const Camera& cam) const
{
	database->getElement()->GetTowerAnimation()->DrawGhost(cam.GetDrawPosition(worldTilePos), gfx, 0);
}

void StateBuildTower::OnClick(GuiGameDatabase * database)
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

void StateBuildGirGui::Draw(const GuiGameDatabase * database, Graphics & gfx, const Camera& cam) const
{
	if (isBegin)
	{
		gfx.DrawCircle(cam.GetDrawPosition(mouseWorldPos), 20, Colors::Magenta);
	}
	else
	{
		const auto drawPos1 = cam.GetDrawPosition(pos);
		const auto drawPos2 = cam.GetDrawPosition(mouseWorldPos);
		gfx.DrawCircle(drawPos1, 20, Colors::Magenta);
		gfx.DrawLine(drawPos1, drawPos2, Colors::Blue);
	}
}

void StateBuildGirGui::OnClick(GuiGameDatabase * database)
{
	if (isBegin)
	{
		pos = mouseWorldPos;
		isBegin = false;
	}
	else
	{
		database->GetMediator().MakeDirectionGuiding(pos, mouseWorldPos);
		isBegin = true;
	}
	
}

void StateBuildBorder::Draw(const GuiGameDatabase * database, Graphics & gfx, const Camera& cam) const
{
	if (isBegin)
	{
		const auto drawPos = cam.GetDrawPosition(database->GetMediator().GetCornerPoint(mouseWorldPos));
		gfx.DrawCircle(drawPos, 6, Colors::Blue);
	}
	else
	{
		const auto drawPos01 = cam.GetDrawPosition(p1);
		const auto drawPos02 = cam.GetDrawPosition(database->GetMediator().GetCornerPoint(mouseWorldPos));
		//draw line
		gfx.DrawLine(drawPos01, drawPos02, Colors::Blue);
		//draw point 1
		gfx.DrawCircle(drawPos01, 6, Colors::Blue);

		//draw point 2
		gfx.DrawCircle(drawPos02, 6, Colors::Blue);
	}
}

void StateBuildBorder::OnClick(GuiGameDatabase * database)
{
	if (isBegin)
	{
		p1 = database->GetMediator().GetCornerPoint(mouseWorldPos);
		isBegin = false;
	}
	else
	{
		database->GetMediator().MakeBorder(p1, mouseWorldPos);
		isBegin = true;
	}
}