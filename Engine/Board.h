#pragma once
#include <vector>
#include <unordered_set>
#include <memory>
#include "Menu.h"
#include "Rect.h"
#include "Graphics.h"
#include "IBoardUpdate.h"
#include "Mouse.h"
#include "IGui.h"
class Tile
{
public:
	Tile(VecI pos)
		:
		pos(pos)
	{}
	void NotifyAll(VecI mousePos)
	{
		for (auto o : observers)
		{
			if (o->GetRect().isContaint(mousePos))
			{
				o->OnNotify();
			}
		}
	}
	void Subcribe(std::shared_ptr<IGui> sub)
	{
		observers.insert(sub);
	}
	void UnSubcribe(std::shared_ptr<IGui> sub)
	{
		observers.erase(sub);
	}
	void ChangeColor()
	{
		c = Colors::Red;
	}
	void Normal()
	{
		c = Colors::Blue;
	}
	void Draw(Graphics& gfx, int width, int height)
	{
		gfx.DrawRectDim(pos + VecI(2,2), width - 2, height - 2, c);
	}
private:
	std::unordered_set<std::shared_ptr<IGui>> observers;
	VecI pos;
	Color c = Colors::Blue;
};

class Board
{
public:
	Board()
	{
		tiles.reserve(nWidth * nHeight);
		for (int h = 0; h < nHeight; h++)
		{
			for (int w = 0; w < nWidth; w++)
			{
				tiles.emplace_back(Tile({ w * width, h * height }));
			}
		}
	}
	void Draw(Graphics& gfx)
	{
		for (auto& t : tiles)
		{
			t.Draw(gfx, width, height);
		}
	}
	void Subcribe(std::shared_ptr<IGui> gui)
	{
		const RectF rect = gui->GetRect();
		const int top = std::max((int)rect.top / height, 0);
		const int left = std::max((int)rect.left / width, 0);
		const int r = ((int)rect.right % width >= 1 ) ? 1 : 0;
		const int b = ((int)rect.bottom % height >= 1 ) ? 1 : 0;
		const int right = std::min(r + (int)rect.right / width, nWidth);
		const int bottom = std::min(b + (int)rect.bottom / height, nHeight);
		for (int h = top; h < bottom; h++)
		{
			for (int w = left; w < right; w++)
			{
				tileAt(w, h).Subcribe(gui);
			}
		}
	}
	void changeStateNormal()
	{
		boardUpdate = &normalState;
	}
	void Update(Mouse& mouse)
	{
		const VecI pos = mouse.GetPos();
		int curTile = pos.x / width + (pos.y / height) * nWidth;
		boardUpdate->Update(this, curTile, mouse);
		prevTile = curTile;
	}
	Tile& tileAt(VecI pos)
	{
		return tiles.at(pos.x / width + (pos.y / height) * nWidth);
	}
	Tile& tileAt(int w, int h)
	{
		return tiles.at(w + h * nWidth);
	}
private:
	friend InitBoardUpdate;
	friend NormalBoardUpdate;
	InitBoardUpdate initState;
	NormalBoardUpdate normalState;
	static constexpr int width = 40;
	static constexpr int height = 40;
	static constexpr int nWidth = Graphics::ScreenWidth / width;
	static constexpr int nHeight = Graphics::ScreenHeight / height;
	std::vector<Tile> tiles;
	IBoardUpdate* boardUpdate = &initState;
	int prevTile = -1;
};