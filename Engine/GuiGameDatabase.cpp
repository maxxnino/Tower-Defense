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

void GuiGameDatabase::OnClick(const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType)
{
	stateMachine->Update(this, worldTilePos, trackingTile, mouseWorldPos, tileType);
}

IMediator& GuiGameDatabase::GetMediator()
{
	return *mediator;
}
