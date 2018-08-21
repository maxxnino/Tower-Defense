#pragma once
#include "IDataItem.h"
class DeleteTower : public IDataItem
{
public:
	void executed(TileGame* tileGame) override;
	Color getColor() override
	{
		return Colors::White;
	}
};