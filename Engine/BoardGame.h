#pragma once
#include <vector>
#include <memory>
#include <random>
#include "TileGame.h"
#include "Mouse.h"
#include "IComponent.h"
class BoardGame : public IComponent
{
public:
	BoardGame(VecF pos, float menuW, float menuH);

	// for game graphic
	void Draw(Graphics& gfx) const noexcept;

	// for game logic
	void ProcessComand(Mouse& mouse);
	
	//for mediator controler
	void AddMediator(IMediator* mediator) override
	{
		this->mediator = mediator;
	}

	//access tile
	inline TileGame& tileAt(int w, int h) noexcept
	{
		assert(w + h * nWidth >= 0 && w + h * nWidth < tiles.size());
		return *tiles[w + h * nWidth];
	}
	inline const TileGame& tileAt(int w, int h) const noexcept
	{
		assert(w + h * nWidth >= 0 && w + h * nWidth < tiles.size());
		return *tiles[w + h * nWidth];
	}
	inline TileGame& tileAt(int index) noexcept
	{
		assert(index >= 0 && index < tiles.size());
		return *tiles[index];
	}
private:
	void MouseMove(const VecI& mousePos) noexcept
	{
		if (prevTile != -1)
		{
			if (curTile != prevTile)
			{
				tiles[curTile]->Awake();
				tiles[prevTile]->Sleep();
				prevTile = curTile;
			}
		}
		else
		{
			tiles[curTile]->Awake();
			prevTile = curTile;
		}
	}
	inline void MouseClick(const VecI& mousePos) noexcept
	{
		tiles.at(curTile)->MouseClick(mousePos, mediator);
	}
private:
	static constexpr int width = 40;
	static constexpr int height = 40;
	int nWidth = -1;
	int nHeight = -1;
	VecF pos;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::vector<std::unique_ptr<TileGame>> tiles;
	IMediator* mediator = nullptr;
	int prevTile = -1;
	int curTile = -1;
};