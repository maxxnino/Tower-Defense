#pragma once
#include <vector>
#include "Mouse.h"
#include "Tile.h"
template <typename T>
class _Board
{
public:
	_Board(VecF pos, float menuW, float menuH)
		:
		pos(pos)
	{
		const int r = ((int)menuW % width >= 1) ? 1 : 0;
		const int b = ((int)menuH % height >= 1) ? 1 : 0;
		nWidth = r + (int)menuW / width;
		nHeight = b + (int)menuH / height;
		tiles.resize(nWidth * nHeight);
		std::fill(tiles.begin(), tiles.end(), Tile());
	}
	void Draw(Graphics& gfx) const
	{
		for (int h = 0; h < nHeight; h++)
		{
			for (int w = 0; w < nWidth; w++)
			{
				const VecI tilePos = (VecI)pos + VecI(w * width, h * height);
				tileAt(w, h).Draw(gfx, tilePos, width, height);
			}
		}
	}
	void Sleep()
	{
		if (prevTile != -1)
		{
			tiles[prevTile].Sleep();
			prevTile = -1;
		}
		curTile = -1;
	}
	void Subcribe(std::shared_ptr<T> gui)
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
				tileAt(w, h).Subcribe(gui);
			}
		}
	}
	void UnSubcribe(std::shared_ptr<T> gui)
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
	void Update()
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
	void ProcessComand(Mouse& mouse)
	{
		const VecI mousePos = mouse.GetPos();
		curTile = (mousePos.x - (int)pos.x) / width + ((mousePos.y - (int)pos.y) / height) * nWidth;
		while (!mouse.IsEmpty())
		{
			const auto e = mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				tiles.at(curTile).NotifyAll(mousePos);
			}
		}
	}
	inline Tile& tileAt(int w, int h)
	{
		return tiles[w + h * nWidth];
	}
	inline const Tile& tileAt(int w, int h) const
	{
		return tiles[w + h * nWidth];
	}
private:
	static constexpr int width = 40;
	static constexpr int height = 40;
	int nWidth = -1;
	int nHeight = -1;
	VecF pos;
	std::vector<Tile> tiles;
	int prevTile = -1;
	int curTile = -1;
};

typedef _Board<IGui> Board;