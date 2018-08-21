#pragma once
#include "Colors.h"
class TileGame;
class IDataItem
{
public:
	virtual void executed(TileGame* tileGame) = 0;
	virtual Color getColor() = 0;
};