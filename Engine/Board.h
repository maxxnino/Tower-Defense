#pragma once
#include <vector>
#include "Mouse.h"
#include "Tile.h"
class Board
{
public:
	Board(VecF pos, float menuW, float menuH)
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
	void Subcribe(std::shared_ptr<IGui> gui);
	void UnSubcribe(std::shared_ptr<IGui> gui);
	void Update();
	void ProcessComand(Mouse& mouse);
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