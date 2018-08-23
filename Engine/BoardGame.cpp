#include "BoardGame.h"
#include "WalkableTile.h"
#include "BuildableTile.h"
#include "MouseState.h"

BoardGame::BoardGame(VecF pos, float menuW, float menuH, IObervable * menuManagerObs, IObervable * mouseState)
	:
	pos(pos),
	mouseState(mouseState)
{
	const int r = ((int)menuW % width >= 1) ? 1 : 0;
	const int b = ((int)menuH % height >= 1) ? 1 : 0;
	nWidth = r + (int)menuW / width;
	nHeight = b + (int)menuH / height;
	const int mid = nHeight / 2;
	for (size_t y = 0; y < nHeight; y++)
	{
		for (size_t x = 0; x < nWidth; x++)
		{
			if (y == mid - 1 || y == mid || y == mid + 1)
			{
				tiles.emplace_back(std::make_unique<WalkableTile>());
				
			}
			else
			{
				tiles.emplace_back(std::make_unique<BuildableTile>());
				tiles.back()->AddObs(menuManagerObs);
			}
		}
	}
}

void BoardGame::Draw(Graphics & gfx) const noexcept
{
	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nWidth; w++)
		{
			const VecI tilePos = (VecI)pos + VecI(w * width, h * height);
			tileAt(w, h).Draw(gfx, tilePos, width, height, mouseState);
		}
	}
}

void BoardGame::ProcessComand(Mouse & mouse)
{
	const VecI mousePos = mouse.GetPos();
	curTile = (mousePos.x - (int)pos.x) / width + ((mousePos.y - (int)pos.y) / height) * nWidth;
	while (!mouse.IsEmpty())
	{
		const auto e = mouse.Read().GetType();
		switch (e)
		{
		case Mouse::Event::Type::LPress:
			MouseClick(mousePos);
			break;
		case Mouse::Event::Type::Move:
			MouseMove(mousePos);
			break;
		case Mouse::Event::Type::RPress:
			static_cast<MouseState*>(mouseState)->typeDame = nullptr;
			break;
		default:
			break;
		}
	}
}

void BoardGame::MouseMove(const VecI & mousePos) noexcept
{
	if (prevTile != -1)
	{
		if (curTile != prevTile)
		{
			tiles.at(curTile)->MouseMove(mousePos);
			tiles.at(prevTile)->MouseMove(mousePos);
			tiles[curTile]->Awake();
			tiles[prevTile]->Sleep();
			prevTile = curTile;
		}
		else
		{
			tiles.at(curTile)->MouseMove(mousePos);
		}
	}
	else
	{
		tiles.at(curTile)->MouseMove(mousePos);
		prevTile = curTile;
		tiles[curTile]->Awake();
	}
}
