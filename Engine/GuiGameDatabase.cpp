#include "GuiGameDatabase.h"
#include "IMediator.h"
void GuiGameDatabase::AddMediator(IMediator* mediator)
{
	this->mediator = mediator;
}

void GuiGameDatabase::Draw(Graphics & gfx, const Camera & cam) const
{
	stateMachine->Draw(this, gfx, cam);
}

void GuiGameDatabase::OnClick()
{
	stateMachine->OnClick(this);
}

void GuiGameDatabase::UpdateOutsideBoard(const b2Vec2 & mouseWorldPos)
{
	stateMachine->UpdateOutsideBoard(mouseWorldPos);
}

void GuiGameDatabase::UpdateInsideBoard(const b2Vec2 & worldTilePos, const VecI & trackingTile, TileType tileType)
{
	stateMachine->UpdateInsideBoard(worldTilePos, trackingTile, tileType);
}

IMediator& GuiGameDatabase::GetMediator()
{
	return *mediator;
}

const IMediator& GuiGameDatabase::GetMediator() const
{
	return *mediator;
}

