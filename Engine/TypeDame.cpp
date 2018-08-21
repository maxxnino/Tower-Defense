#include "TypeDame.h"
#include "BuildableTile.h"
void TypeDame::executed(TileGame * tileGame)
{
	static_cast<BuildableTile*>(tileGame)->BuildTower(this);
}
