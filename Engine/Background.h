#pragma once
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <random>
#include "Camera.h"
#include "MouseCameraController.h"
#include "Mouse.h"
#include "IComponent.h"
#include "GameSettings.h"
#include "Surface.h"
#include "Codex.h"
namespace std
{
	template <>
	struct hash<VecI>
	{
		size_t operator()(const VecI& vec) const
		{
			std::hash<int> hasher;
			auto hashx = hasher(vec.x);
			auto hashy = hasher(vec.y);
			hashx ^= hashy + 0x9e3779b9 + (hashx << 6) + (hashx >> 2);
			return hashx;
		}
	};
	template <>
	struct equal_to<VecI>
	{
		size_t operator()(const VecI& lhs, const VecI& rhs) const
		{
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}
	};
}
class Background : public IComponent
{
public:
	Background(const b2Vec2& pos, int gridWidth, int gridHeight, int tileWorldSize, std::mt19937& rng)
		:
		pos(pos),
		tileWorldSize(tileWorldSize),
		tileScreenSize(tileWorldSize * Camera::scalePixel),
		gridWidth(gridWidth),
		gridHeight(gridHeight)
	{
		// generate tile surface
		surfs.emplace_back(Codex<Surface>::Retrieve(L"Images\\Tile\\ground_01.png"));
		surfs.emplace_back(Codex<Surface>::Retrieve(L"Images\\Tile\\ground_02.png"));
		surfs.emplace_back(Codex<Surface>::Retrieve(L"Images\\Tile\\ground_03.png"));
		surfs.emplace_back(Codex<Surface>::Retrieve(L"Images\\Tile\\ground_01_cur.png"));
		surfs.emplace_back(Codex<Surface>::Retrieve(L"Images\\Tile\\ground_02_cur.png"));
		surfs.emplace_back(Codex<Surface>::Retrieve(L"Images\\Tile\\ground_03_cur.png"));

		// reserve tile map space
		std::uniform_int_distribution<int> type(0, 2);
		nWidth = gridWidth / tileWorldSize;
		nHeight = gridHeight / tileWorldSize;
		tiles.reserve(nWidth * nHeight);
		// load tile grid from map string (B is 0, C is 1 A is -1 etc.)
		{
			//auto mi = map.cbegin();
			for (int n = 0; n < nWidth * nHeight; n++)//, ++mi)
			{
				//tiles.push_back(*mi - 'B');
				tiles.push_back(type(rng));
			}
		}
	}
	void Draw(Graphics& gfx, const Camera& cam) const
	{
		auto rectClip = (RectI)cam.GetViewportRect().DisplaceBy(VecF(-pos.x, -pos.y)).ClipToBox2D(RectF(0, float(gridHeight), float(gridWidth), 0));
		const int top = std::min(1 + rectClip.top / tileWorldSize, nHeight);
		const int right = std::min(1 + rectClip.right / tileWorldSize, nWidth);
		const int bottom = rectClip.bottom / tileWorldSize;
		const int left = rectClip.left / tileWorldSize;
		for (int y = bottom; y < top; y++)
		{
			for (int x = left; x < right; x++)
			{
				const int index = GetTileAt(x, y);
				const auto drawPos = cam.GetDrawPosition(b2Vec2(float32(x * tileWorldSize), float32(y * tileWorldSize)) + pos);
				if (x == trackingTile.x && y == trackingTile.y)
				{
					gfx.DrawSprite(drawPos.x, drawPos.y, *surfs[index + 3], SpriteEffect::Copy{});
				}
				else
				{
					gfx.DrawSprite(drawPos.x, drawPos.y, *surfs[index], SpriteEffect::Copy{});
				}
			}
		}
		mediator->GetDatabase()->Draw(gfx, cam);
	}
	void Update(Mouse& mouse, const Camera& cam, MouseCameraController& controller)
	{
		const auto mouseWorldPos = cam.ScreenToWorldPos((VecF)mouse.GetPos());
		const auto mouseTilePos = mouseWorldPos - pos;
		mediator->SetMousePos(mouseWorldPos);
		if (mouseTilePos.x >= 0 && mouseTilePos.x < gridWidth &&
			mouseTilePos.y >= 0 && mouseTilePos.y < gridHeight)
		{
			// Todo: need to fix trackingTile go outside of vector tiles
			trackingTile.x = (int)mouseTilePos.x / tileWorldSize;
			trackingTile.y = std::min((int)mouseTilePos.y / tileWorldSize + 1, nHeight);
			const auto worldTilePos = b2Vec2(float(trackingTile.x * tileWorldSize), float(trackingTile.y * tileWorldSize)) + pos;
			mediator->GetDatabase()->SetPos(worldTilePos);
			while (!mouse.IsEmpty())
			{
				const auto e = mouse.Read().GetType();
				switch (e)
				{
				case Mouse::Event::Type::LPress:
				{
					if (GetTileAt(trackingTile.x, trackingTile.y) > 0)
					{
						auto tower = towerTiles.find(trackingTile);
						if (tower != towerTiles.end())
						{
							mediator->GetDatabase()->UpdateHaveTower(worldTilePos, trackingTile, mouseWorldPos, tower->second);
						}
						else if(mediator->GetDatabase()->UpdateNoTower(worldTilePos, mouseWorldPos))
						{
							controller.ProcessCommand(e);
						}
					}
					else if(mediator->GetDatabase()->UpdateNoBuildTile(worldTilePos, mouseWorldPos))
					{
						controller.ProcessCommand(e);
					}
					break;
				}
				case Mouse::Event::Type::RPress:
					mediator->OnRightClickFromGUI();
					break;
				case Mouse::Event::Type::LRelease:
					controller.ProcessCommand(e);
					break;
				}
			}
		}
		else
		{
			while (!mouse.IsEmpty())
			{
				controller.ProcessCommand(mouse.Read().GetType());
			}
		}
		controller.Update();
	}
	void SwapTower(const VecI& tilePos01, int newIndex01, const VecI& tilePos02, int newIndex02)
	{
		assert(towerTiles.find(tilePos01) != towerTiles.end());
		assert(towerTiles.find(tilePos02) != towerTiles.end());
		towerTiles.find(tilePos01)->second = newIndex01;
		towerTiles.find(tilePos02)->second = newIndex02;
	}
	void AddMediator(IMediator* mediator) override
	{
		this->mediator = mediator;
	}
	void AddTower(int towerIndex)
	{
		towerTiles.emplace(trackingTile, towerIndex);
	}
private:
	inline int GetTileAt(int x, int y) const
	{
		return tiles[y * nWidth + x];
	}
private:
	b2Vec2 pos;
	int tileWorldSize;
	int tileScreenSize;
	int gridWidth;
	int gridHeight;
	int nWidth;
	int nHeight;
	VecI trackingTile;
	// vector of surface
	std::vector<std::shared_ptr<Surface>> surfs;
	// grid of tiles (indices into the surfs vector)
	std::vector<int> tiles;
	//tower tile VecI pos, tower index in world
	std::unordered_map<VecI, int> towerTiles;
	IMediator* mediator = nullptr;
};