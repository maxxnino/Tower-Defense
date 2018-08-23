#pragma once
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <memory>
#include "Tile.h"
#include "Entity.h"
class Board
{
public:
	Board(int nWidth, int nHeight)
		:
		nWidth(nWidth),
		nHeight(nHeight)
	{
		tiles.resize(nWidth * nHeight);
		std::fill(tiles.begin(), tiles.end(), tile());
	}
	void additem(std::unique_ptr<Entity> entity)
	{
		const RectF rect = entity->getRect();
		const int top = std::max((int)(rect.top) / height, 0);
		const int left = std::max((int)(rect.left) / width, 0);
		const int r = ((int)(rect.right) % width >= 1) ? 1 : 0;
		const int b = ((int)(rect.bottom) % height >= 1) ? 1 : 0;
		const int right = std::min(r + (int)(rect.right) / width, nWidth);
		const int bottom = std::min(b + (int)(rect.bottom) / height, nHeight);
		for (int h = top; h < bottom; h++)
		{
			for (int w = left; w < right; w++)
			{
				tileat(w, h).additem(entity);
			}
		}
	}
	inline tile& tileat(int w, int h)
	{
		return tiles[w + h * nWidth];
	}
	inline const tile& tileat(int w, int h) const
	{
		return tiles[w + h * nHeight];
	}
private:
	std::vector<tile> tiles;
	static int width;
	static int height;
	int nWidth;
	int nHeight;
};