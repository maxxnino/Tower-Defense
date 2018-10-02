//#pragma once
//#include <vector>
//#include <memory>
//#include <random>
//#include "IComponent.h"
//#include "WalkableTile.h"
//#include "BuildableTile.h"
//#include "Mouse.h"
//#include "GameSettings.h"
//#include "MouseCameraController.h"
//class BoardGame : public IComponent
//{
//public:
//	BoardGame(const std::wstring& filename)
//	{
//		GameSettings::Get().AddMapData(filename);
//		pos = { GameSettings::Get().GetData("[PosX]"),GameSettings::Get().GetData("[PosY]") };
//		nWidth = (int)GameSettings::Get().GetData("[nWidth]");
//		nHeight = (int)GameSettings::Get().GetData("[nHeight]");
//		boardWidth = nWidth * tileWidth;
//		boardHeight = nHeight * tileHeight;
//		auto data = GameSettings::Get().GetMapData("*MAP*");
//		for (int i= 0; i < nWidth * nHeight; i++)
//		{
//			for (auto d : data)
//			{
//				if (d == '1')
//				{
//					tiles.emplace_back(std::make_unique<WalkableTile>(pos, i, Codex<Surface>::Retrieve(L"Images\\Tile\\ground_01.png")));
//				}
//				else if (d == '0')
//				{
//					tiles.emplace_back(std::make_unique<BuildableTile>(pos, i, Codex<Surface>::Retrieve(L"Images\\Tile\\ground_02.png")));
//				}
//			}
//		}
//	}
//	BoardGame(VecF pos, int nWidth, int nHeight)
//		:
//		pos(pos),
//		nWidth(nWidth),
//		nHeight(nHeight)
//	{
//		boardWidth = nWidth * tileWidth;
//		boardHeight = nHeight * tileHeight;
//		const int mid = nHeight / 2;
//		for (int y = 0; y < nHeight; y++)
//		{
//			for (int x = 0; x < nWidth; x++)
//			{
//				const VecI pos = VecI(x * tileWidth, y  * tileHeight);
//				if (y == mid - 1 || y == mid || y == mid + 1)
//				{
//					tiles.emplace_back(std::make_unique<WalkableTile>(pos, x + y * nWidth, Codex<Surface>::Retrieve(L"Images\\Tile\\ground_01.png")));
//				}
//				else
//				{
//					std::uniform_int_distribution<int> seed(2,3);
//					switch (seed(rng))
//					{
//					case 1:
//						tiles.emplace_back(std::make_unique<BuildableTile>(pos, x + y * nWidth, Codex<Surface>::Retrieve(L"Images\\Tile\\ground_02.png")));
//						break;
//					case 2:
//						tiles.emplace_back(std::make_unique<BuildableTile>(pos, x + y * nWidth, Codex<Surface>::Retrieve(L"Images\\Tile\\ground_03.png")));
//						break;
//					default:
//						tiles.emplace_back(std::make_unique<BuildableTile>(pos, x + y * nWidth, Codex<Surface>::Retrieve(L"Images\\Tile\\ground_02.png")));
//						break;
//					}
//				}
//			}
//		}
//	}
//	void SaveMap()
//	{
//		std::ofstream file("Data\\map01.ini");
//		file << "[PosX]\n" << 0 << "\n" << "[PosY]\n" << 0 << "\n";
//		file << "[nWidth]\n" << nWidth << "\n" << "[nHeight]\n" << nHeight << "\n";
//		file << "*MAP*\n";
//		for (int i = 0; i < nWidth * nHeight; i++)
//		{
//			file << tiles[i]->GetTileData();
//		}
//	}
//	// for game graphic
//	void Draw(Graphics& gfx, const VecI& camPos) const noexcept
//	{
//		const RectF boardRect = RectF(pos, (float)boardWidth, (float)boardHeight);
//		const RectF rect = mouseController->GetRect().GetClippedTo(boardRect);
//
//		const int left = (int)rect.left / tileWidth;
//		const int top = (int)rect.top / tileHeight;
//		const int right = std::min((int)rect.right / tileWidth + 1, nWidth);
//		const int bottom = std::min((int)rect.bottom / tileHeight + 1, nHeight);
//		for (int h = top; h < bottom; h++)
//		{
//			for (int w = left; w < right; w++)
//			{
//				const VecI tilePos = (VecI)pos + VecI(w * tileWidth, h * tileHeight) + camPos;
//				tileAt(w, h).Draw(gfx, tilePos, tileWidth, tileHeight);
//			}
//		}
//	}
//	void DrawTest(Graphics& gfx,const VecI& camPos) const
//	{
//		for (int h = 0; h < nHeight; h++)
//		{
//			for (int w = 0; w < nWidth; w++)
//			{
//				const VecI tilePos = (VecI)pos + VecI(w * tileWidth, h * tileHeight) + camPos;
//				tileAt(w, h).Draw(gfx, tilePos, tileWidth, tileHeight);
//			}
//		}
//	}
//	// for game logic
//	void ProcessComand(Mouse& mouse,const VecI& camPos)
//	{
//		mousePos = mouse.GetPos();
//		const int posX = mousePos.x - (int)pos.x - camPos.x;
//		const int posY = mousePos.y - (int)pos.y - camPos.y;
//		if (posX >= 0 && posX < boardWidth && posY >= 0 && posY < boardHeight)
//		{
//			curTile = { posX / tileWidth ,posY / tileHeight };
//			mediator->GetMouseGame()->SetPos({ curTile.x * tileWidth + camPos.x,curTile.y * tileHeight + camPos.y });
//			isInsideBoard = true;
//		}
//		else
//		{
//			isInsideBoard = false;
//			mediator->GetMouseGame()->SetPos({ mousePos.x - tileWidth / 2, mousePos.y - tileHeight / 2 });
//		}
//		auto mouseState = mediator->GetMouseGame()->GetMouseState();
//		
//		while (!mouse.IsEmpty())
//		{
//			const auto e = mouse.Read().GetType();
//			switch (e)
//			{
//			case Mouse::Event::Type::LPress:
//			{
//				if (isInsideBoard)
//				{
//					switch (mouseState)
//					{
//					case None:
//						if (tileAt(curTile).MouseNoneClick(mediator))
//						{
//							mouseController->ProcessCommand(true, mousePos);
//						}
//						break;
//					case BuildTower:
//						tileAt(curTile).MouseBuildTowerClick(mediator);
//						break;
//					case DeleteTower:
//						tileAt(curTile).MouseDeleteTowerClick(mediator);
//						break;
//					case SwapTower:
//						break;
//					}
//				}
//				else
//				{
//					mouseController->ProcessCommand(true, mousePos);
//				}
//				break;
//			}
//			case Mouse::Event::Type::LRelease:
//				mouseController->ProcessCommand(false, mousePos);
//				break;
//			case Mouse::Event::Type::RPress:
//				mediator->OnRightClickFromGUI();
//				break;
//			default:
//				break;
//			}
//		}
//		mouseController->Update(mouse);
//	}
//	void AddMouseController(MouseCameraController* mouse)
//	{
//		mouseController = mouse;
//		const RectF rect = { (float)pos.x,(float)pos.y, (float)pos.x + (float)boardWidth, (float)pos.y + (float)boardHeight};
//		mouse->SetCameraBorder(rect.GetExpanded((float)tileWidth * 4.0f));
//	}
//	//for mediator controler
//	void AddMediator(IMediator* mediator) override
//	{
//		this->mediator = mediator;
//	}
//
//	//access tile
//	inline TileGame& tileAt(int w, int h) noexcept
//	{
//		assert(w + h * nWidth >= 0 && w + h * nWidth < tiles.size());
//		return *tiles[w + h * nWidth];
//	}
//	inline const TileGame& tileAt(int w, int h) const noexcept
//	{
//		assert(w + h * nWidth >= 0 && w + h * nWidth < tiles.size());
//		return *tiles[w + h * nWidth];
//	}
//	inline TileGame& tileAt(VecI curtile) noexcept
//	{
//		assert(curtile.x + curtile.y * nWidth >= 0 && curtile.x + curtile.y * nWidth < tiles.size());
//		return *tiles[curtile.x + curtile.y * nWidth];
//	}
//	inline const TileGame& tileAt(VecI curtile) const noexcept
//	{
//		assert(curtile.x + curtile.y * nWidth >= 0 && curtile.x + curtile.y * nWidth < tiles.size());
//		return *tiles[curtile.x + curtile.y * nWidth];
//	}
//	inline TileGame& tileAt(int index) noexcept
//	{
//		assert(index >= 0 && index < tiles.size());
//		return *tiles[index];
//	}
//private:
//	inline void MouseClick(const VecI& mousePos) noexcept
//	{
//		tileAt(curTile).MouseClick(mousePos, mediator);
//	}
//public:
//	static constexpr int tileWidth = 40;
//	static constexpr int tileHeight = 40;
//private:
//	int nWidth = -1;
//	int nHeight = -1;
//	int boardWidth;
//	int boardHeight;
//	VecF pos;
//	std::mt19937 rng = std::mt19937(std::random_device{}());
//	std::vector<std::unique_ptr<TileGame>> tiles;
//	IMediator* mediator = nullptr;
//	VecI curTile = {0,0};
//	MouseCameraController* mouseController = nullptr;
//	bool isInsideBoard = true;
//	VecI mousePos;
//};