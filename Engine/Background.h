#pragma once
#include <algorithm>
#include <vector>
#include <random>
#include "Camera.h"
#include "Mouse.h"
#include "IComponent.h"
#include "GameSettings.h"
#include "Surface.h"
#include "Codex.h"
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
	}
	void Update(Mouse& mouse, const Camera& cam)
	{
		const auto mouseWorldPos = cam.ScreenToWorldPos((VecF)mouse.GetPos());
		const auto mouseTilePos = mouseWorldPos - pos;
		
		if (mouseTilePos.x >= 0 && mouseTilePos.x < gridWidth &&
			mouseTilePos.y >= 0 && mouseTilePos.y < gridHeight)
		{
			trackingTile.x = (int)mouseTilePos.x / tileWorldSize;
			trackingTile.y = std::max((int)mouseTilePos.y / tileWorldSize + 1, 0 );

			const auto worldTilePos = b2Vec2(float(trackingTile.x * tileWorldSize), float(trackingTile.y * tileWorldSize)) + pos;
			const auto mouseState = mediator->GetMouseGame()->GetMouseState();
			while (!mouse.IsEmpty())
			{
				const auto e = mouse.Read().GetType();
				switch (e)
				{
				case Mouse::Event::Type::LPress:
				{
					if (tiles[trackingTile.x + trackingTile.y * nWidth] > 0)
						mediator->MouseClickOnBackground(mouseState, mouseWorldPos, worldTilePos);
					break;
				}
				case Mouse::Event::Type::RPress:
					mediator->OnRightClickFromGUI();
					break;
				default:
					break;
				}
			}
		}
		else
		{
			
		}
	}
	/*void ProcessComand(Mouse& mouse, const VecI& camPos)
	{
		mousePos = mouse.GetPos();
		const int posX = mousePos.x - (int)pos.x - camPos.x;
		const int posY = mousePos.y - (int)pos.y - camPos.y;
		if (posX >= 0 && posX < boardWidth && posY >= 0 && posY < boardHeight)
		{
			curTile = { posX / tileWidth ,posY / tileHeight };
			mediator->GetMouseGame()->SetPos({ curTile.x * tileWidth + camPos.x,curTile.y * tileHeight + camPos.y });
			isInsideBoard = true;
		}
		else
		{
			isInsideBoard = false;
			mediator->GetMouseGame()->SetPos({ mousePos.x - tileWidth / 2, mousePos.y - tileHeight / 2 });
		}
		auto mouseState = mediator->GetMouseGame()->GetMouseState();

		while (!mouse.IsEmpty())
		{
			const auto e = mouse.Read().GetType();
			switch (e)
			{
			case Mouse::Event::Type::LPress:
			{
				if (isInsideBoard)
				{
					switch (mouseState)
					{
					case None:
						if (tileAt(curTile).MouseNoneClick(mediator))
						{
							mouseController->ProcessCommand(true, mousePos);
						}
						break;
					case BuildTower:
						tileAt(curTile).MouseBuildTowerClick(mediator);
						break;
					case DeleteTower:
						tileAt(curTile).MouseDeleteTowerClick(mediator);
						break;
					case SwapTower:
						break;
					}
				}
				else
				{
					mouseController->ProcessCommand(true, mousePos);
				}
				break;
			}
			case Mouse::Event::Type::LRelease:
				mouseController->ProcessCommand(false, mousePos);
				break;
			case Mouse::Event::Type::RPress:
				mediator->OnRightClickFromGUI();
				break;
			default:
				break;
			}
		}
		mouseController->Update(mouse);
	}*/
	void AddMediator(IMediator* mediator) override
	{
		this->mediator = mediator;
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
	IMediator* mediator = nullptr;
};