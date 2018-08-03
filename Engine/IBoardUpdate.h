#pragma once
#include "Mouse.h"
class Board;
class IBoardUpdate
{
public:
	virtual void Update(Board* board, int curTile, Mouse& mouse) = 0;
};

class InitBoardUpdate : public IBoardUpdate
{
public:
	void Update(Board* board, int curTile, Mouse& mouse) override;
};

class NormalBoardUpdate : public IBoardUpdate
{
public:
	void Update(Board* board, int curTile, Mouse& mouse) override;
};