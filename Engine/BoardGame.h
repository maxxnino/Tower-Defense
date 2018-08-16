#pragma once
#include <vector>
#include <memory>
#include "WalkableTile.h"
#include "BuildableTile.h"
#include "Mouse.h"
#include "Tower.h"
#include "ContactListener.h"
class BoardGame
{
public:
	BoardGame(VecF pos, float menuW, float menuH)
		:
		pos(pos)
	{
		const int r = ((int)menuW % width >= 1) ? 1 : 0;
		const int b = ((int)menuH % height >= 1) ? 1 : 0;
		nWidth = r + (int)menuW / width;
		nHeight = b + (int)menuH / height;
		for (size_t y = 0; y < nHeight; y++)
		{
			for (size_t x = 0; x < nWidth; x++)
			{
				if ((x % 2) == 0)
				{
					tiles.emplace_back(std::make_unique<BuildableTile>());
				}
				else
				{
					tiles.emplace_back(std::make_unique<WalkableTile>());
				}
				
			}
		}
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
	void AddListener(ContactListener* newListener)
	{
		listener = newListener;
	}
	void Update()
	{
		
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
	inline TileGame& tileAt(int w, int h)
	{
		return *tiles[w + h * nWidth];
	}
	inline const TileGame& tileAt(int w, int h) const
	{
		return *tiles[w + h * nWidth];
	}
private:
	inline void MouseMove(const VecI& mousePos) noexcept
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
	inline void MouseClick(const VecI& mousePos) noexcept
	{
		tiles.at(curTile)->MouseClick(mousePos, listener);
	}
private:
	static constexpr int width = 40;
	static constexpr int height = 40;
	int nWidth = -1;
	int nHeight = -1;
	VecF pos;
	std::vector<std::unique_ptr<TileGame>> tiles;
	int prevTile = -1;
	int curTile = -1;
	ContactListener* listener = nullptr;
};