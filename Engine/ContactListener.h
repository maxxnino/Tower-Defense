#pragma once
#include <memory>
#include "Tower.h"
#include "MouseCommand.h"
class TileGame;
class ContactListener
{
public:
	void OnClick(TileGame* tile);
	void AddMouseCommand(MouseCommand* newMouseCommand)
	{
		mouseCommand = newMouseCommand;
	}
private:
	MouseCommand* mouseCommand = nullptr;
};