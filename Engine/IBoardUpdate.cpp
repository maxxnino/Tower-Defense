#include "IBoardUpdate.h"
#include "Board.h"
void InitBoardUpdate::Update(Board * board, int curTile, Mouse& mouse)
{
	board->tiles.at(curTile).ChangeColor();
	
	board->changeStateNormal();
}

void NormalBoardUpdate::Update(Board * board, int curTile, Mouse& mouse)
{
	board->tiles.at(curTile).ChangeColor();
	while (!mouse.IsEmpty())
	{
		auto e = mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			board->tiles.at(curTile).NotifyAll(mouse.GetPos());
		}
	}
	if (curTile != board->prevTile)
	{
		board->tiles.at(board->prevTile).Normal();
	}
}
