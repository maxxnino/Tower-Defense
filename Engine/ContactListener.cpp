#include "ContactListener.h"
#include "TileGame.h"
void ContactListener::OnClick(TileGame* tile)
{
	assert(mouseCommand);
	tile->Upgrade(mouseCommand->GetType());
}
