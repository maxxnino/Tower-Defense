#include "BoardGame.h"
#include "WalkableTile.h"
#include "BuildableTile.h"

BoardGame::BoardGame(VecF pos, float menuW, float menuH)
	:
	pos(pos)
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
				VecI pos = VecI((int)x * width, (int)y  * height);
				tiles.emplace_back(std::make_unique<BuildableTile>(pos,int(x + y * nWidth)));
				//tiles.back()->AddObs(menuManagerObs);
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
			tileAt(w, h).Draw(gfx, tilePos, width, height);
		}
	}
	auto typeDame = mediator->GetMouseGame()->typeDame;
	if (typeDame)
	{
		const VecI tilePos = (VecI)pos + VecI(curTile.x * width, curTile.y * height);
		tileAt(curTile).DrawActive(gfx, tilePos, width, height, typeDame->getColor());
	}
	
}

void BoardGame::ProcessComand(Mouse & mouse)
{
	const VecI mousePos = mouse.GetPos();
	while (!mouse.IsEmpty())
	{
		const auto e = mouse.Read().GetType();
		switch (e)
		{
		case Mouse::Event::Type::LPress:
			MouseClick(mousePos);
			break;
		case Mouse::Event::Type::Move:
			curTile = { (mousePos.x - (int)pos.x) / width ,(mousePos.y - (int)pos.y) / height };
			break;
		case Mouse::Event::Type::RPress:
			mediator->GetMouseGame()->typeDame = nullptr;
			break;
		default:
			break;
		}
	}
}
