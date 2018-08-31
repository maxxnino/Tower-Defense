#pragma once
#include <vector>
#include <memory>
#include <random>
#include "TileGame.h"
#include "Mouse.h"
class BoardGame
{
public:
	BoardGame(VecF pos, float menuW, float menuH);
	void Draw(Graphics& gfx) const noexcept;
	void ProcessComand(Mouse& mouse);
	inline TileGame& tileAt(int w, int h)
	{
		return *tiles[w + h * nWidth];
	}
	inline const TileGame& tileAt(int w, int h) const
	{
		return *tiles[w + h * nWidth];
	}
private:
	void MouseMove(const VecI& mousePos) noexcept;
	inline void MouseClick(const VecI& mousePos) noexcept
	{
		tiles.at(curTile)->MouseClick(mousePos);
	}
private:
	static constexpr int width = 40;
	static constexpr int height = 40;
	int nWidth = -1;
	int nHeight = -1;
	VecF pos;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::vector<std::unique_ptr<TileGame>> tiles;
	int prevTile = -1;
	int curTile = -1;
};