#include "GuiGameDatabase.h"
#include "IMediator.h"
void GuiGameDatabase::AddMediator(IMediator* mediator)
{
	this->mediator = mediator;
}

void GuiGameDatabase::Draw(Graphics & gfx, const Camera & cam) const
{
	const auto drawPos = cam.GetDrawPosition(pos);
	stateMachine->Draw(this, gfx, drawPos);
}

void GuiGameDatabase::UpdateHaveTower(const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos,int towerIndex)
{
	stateMachine->UpdateHaveTower(this, worldTilePos, trackingTile, mouseWorldPos, towerIndex);
	
}

bool GuiGameDatabase::UpdateNoTower(const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos)
{
	return stateMachine->UpdateNoTower(this, worldTilePos, mouseWorldPos);
	
}

bool GuiGameDatabase::UpdateNoBuildTile(const b2Vec2 & worldTilePos, const b2Vec2 & mouseWorldPos)
{
	return stateMachine->UpdateNoBuildTile(this, worldTilePos, mouseWorldPos);
	
}

IMediator& GuiGameDatabase::GetMediator()
{
	return *mediator;
}
