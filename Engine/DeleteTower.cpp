#include "DeleteTower.h"
#include "BuildableTile.h"
void DeleteTower::executed(TileGame * tileGame)
{
	static_cast<BuildableTile*>(tileGame)->DeleteTower();
}
