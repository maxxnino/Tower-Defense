#include "Board.h"

void Board::Subcribe(std::shared_ptr<IGui> gui)
{
	const RectF rect = gui->GetRect();
	const int top = std::max((int)(rect.top - pos.y) / height, 0);
	const int left = std::max((int)(rect.left - pos.x)/ width, 0);
	const int r = ((int)(rect.right - pos.x) % width >= 1) ? 1 : 0;
	const int b = ((int)(rect.bottom - pos.y) % height >= 1) ? 1 : 0;
	const int right = std::min(r + (int)(rect.right - pos.x) / width, nWidth);
	const int bottom = std::min(b + (int)(rect.bottom - pos.y)/ height, nHeight);
	for (int h = top; h < bottom; h++)
	{
		for (int w = left; w < right; w++)
		{
			tileAt(w, h).Subcribe(gui);
		}
	}
}

void Board::UnSubcribe(std::shared_ptr<IGui> gui)
{
	const RectF rect = gui->GetRect();
	const int top = std::max((int)(rect.top - pos.y) / height, 0);
	const int left = std::max((int)(rect.left - pos.x) / width, 0);
	const int r = ((int)(rect.right - pos.x) % width >= 1) ? 1 : 0;
	const int b = ((int)(rect.bottom - pos.y) % height >= 1) ? 1 : 0;
	const int right = std::min(r + (int)(rect.right - pos.x) / width, nWidth);
	const int bottom = std::min(b + (int)(rect.bottom - pos.y) / height, nHeight);
	for (int h = top; h < bottom; h++)
	{
		for (int w = left; w < right; w++)
		{
			tileAt(w, h).UnSubcribe(gui);
		}
	}
}

void Board::Update()
{
	tiles.at(curTile).Awake();
	if (curTile != prevTile)
	{
		if (prevTile != -1)
		{
			tiles.at(prevTile).Sleep();
		}
		prevTile = curTile;
	}
}

void Board::ProcessComand(Mouse & mouse)
{
	const VecI mousePos = mouse.GetPos();
	curTile = (int)(mousePos.x - pos.x) / width + ((int)(mousePos.y - pos.y)/ height) * nWidth;
	while (!mouse.IsEmpty())
	{
		const auto e = mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			tiles.at(curTile).NotifyAll(mousePos);
		}
	}
}
