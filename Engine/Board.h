#pragma once
#include <vector>
#include "Mouse.h"
#include "Tile.h"
template <typename Entity>
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
		std::fill(tiles.begin(), tiles.end(), _Tile<Entity>());
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
	void AddItem(std::shared_ptr<Entity> entity)
	{
		const RectF rect = entity->GetRect();
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
				tileAt(w, h).AddItem(entity);
			}
		}
	}
	void ProcessComand(Mouse& mouse)
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
			default:
				break;
			}
		}
	}
	inline _Tile<Entity>& tileAt(int w, int h)
	{
		return tiles[w + h * nWidth];
	}
	inline const _Tile<Entity>& tileAt(int w, int h) const
	{
		return tiles[w + h * nWidth];
	}
private:
	inline void MouseMove(const VecI& mousePos) noexcept
	{
		if (prevTile != -1)
		{
			if (curTile != prevTile)
			{
				tiles.at(curTile).MouseMove(mousePos);
				tiles.at(prevTile).MouseMove(mousePos);
				prevTile = curTile;
			}
			else
			{
				tiles.at(curTile).MouseMove(mousePos);
			}
		}
		else
		{
			tiles.at(curTile).MouseMove(mousePos);
			prevTile = curTile;
		}
	}
	inline void MouseClick(const VecI& mousePos) noexcept
	{
		tiles.at(curTile).MouseClick(mousePos);
	}
private:
	static constexpr int width = 40;
	static constexpr int height = 40;
	int nWidth = -1;
	int nHeight = -1;
	VecF pos;
	std::vector<_Tile<Entity>> tiles;
	int prevTile = -1;
	int curTile = -1;
};

typedef _Board<IGui> BoardGUI;