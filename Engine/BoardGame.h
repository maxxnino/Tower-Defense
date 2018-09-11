#pragma once
#include <vector>
#include <memory>
#include <random>
#include "IComponent.h"
#include "WalkableTile.h"
#include "BuildableTile.h"
#include "Mouse.h"
class BoardGame : public IComponent
{
public:
	BoardGame(VecF pos, float menuW, float menuH)
		:
		pos(pos)
	{
		const int r = ((int)menuW % tileWidth >= 1) ? 1 : 0;
		const int b = ((int)menuH % tileHeight >= 1) ? 1 : 0;
		nWidth = r + (int)menuW / tileWidth;
		nHeight = b + (int)menuH / tileHeight;
		const int mid = nHeight / 2;
		for (int y = 0; y < nHeight; y++)
		{
			for (int x = 0; x < nWidth; x++)
			{
				const VecI pos = VecI(x * tileWidth, y  * tileHeight);
				if (y == mid - 1 || y == mid || y == mid + 1)
				{
					tiles.emplace_back(std::make_unique<WalkableTile>(pos, x + y * nWidth, Codex<Surface>::Retrieve(L"Images\\ground_01.png")));
				}
				else
				{
					std::uniform_int_distribution<int> seed(2,3);
					switch (seed(rng))
					{
					case 1:
						tiles.emplace_back(std::make_unique<BuildableTile>(pos, x + y * nWidth, Codex<Surface>::Retrieve(L"Images\\ground_02.png")));
						break;
					case 2:
						tiles.emplace_back(std::make_unique<BuildableTile>(pos, x + y * nWidth, Codex<Surface>::Retrieve(L"Images\\ground_03.png")));
						break;
					default:
						tiles.emplace_back(std::make_unique<BuildableTile>(pos, x + y * nWidth, Codex<Surface>::Retrieve(L"Images\\ground_02.png")));
						break;
					}
				}
			}
		}
	}

	// for game graphic
	void Draw(Graphics& gfx) const noexcept
	{
		for (int h = 0; h < nHeight; h++)
		{
			for (int w = 0; w < nWidth; w++)
			{
				const VecI tilePos = (VecI)pos + VecI(w * tileWidth, h * tileHeight);
				tileAt(w, h).Draw(gfx, tilePos, tileWidth, tileHeight);
			}
		}
		auto element = mediator->GetMouseGame()->getElement();
		if (element)
		{
			const VecI tilePos = (VecI)pos + VecI(curTile.x * tileWidth, curTile.y * tileHeight);
			gfx.DrawSprite(tilePos.x, tilePos.y, *element->GetSurface(), SpriteEffect::AlphaBlendBaked{});
		}
	}

	// for game logic
	void ProcessComand(Mouse& mouse)
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
				curTile = { (mousePos.x - (int)pos.x) / tileWidth ,(mousePos.y - (int)pos.y) / tileHeight };
				break;
			case Mouse::Event::Type::RPress:
				mediator->OnRightClickFromGUI();
				break;
			default:
				break;
			}
		}
	}
	
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
	inline TileGame& tileAt(VecI curtile) noexcept
	{
		assert(curtile.x + curtile.y * nWidth >= 0 && curtile.x + curtile.y * nWidth < tiles.size());
		return *tiles[curtile.x + curtile.y * nWidth];
	}
	inline const TileGame& tileAt(VecI curtile) const noexcept
	{
		assert(curtile.x + curtile.y * nWidth >= 0 && curtile.x + curtile.y * nWidth < tiles.size());
		return *tiles[curtile.x + curtile.y * nWidth];
	}
	inline TileGame& tileAt(int index) noexcept
	{
		assert(index >= 0 && index < tiles.size());
		return *tiles[index];
	}
private:
	inline void MouseClick(const VecI& mousePos) noexcept
	{
		tileAt(curTile).MouseClick(mousePos, mediator);
	}
public:
	static constexpr int tileWidth = 40;
	static constexpr int tileHeight = 40;
private:
	int nWidth = -1;
	int nHeight = -1;
	VecF pos;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::vector<std::unique_ptr<TileGame>> tiles;
	IMediator* mediator = nullptr;
	VecI curTile = {0,0};
};