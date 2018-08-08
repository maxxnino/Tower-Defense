#pragma once
#include <unordered_set>
#include "Rect.h"
#include "Graphics.h"
#include "IGui.h"
template <typename T>
class _Tile
{
public:
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
	void Subcribe(std::shared_ptr<T> sub)
	{
		observers.insert(sub);
	}
	void UnSubcribe(std::shared_ptr<T> sub)
	{
		observers.erase(sub);
	}
	void Awake()
	{
		c = Colors::Red;
	}
	void Sleep()
	{
		c = Colors::Blue;
	}
	void Draw(Graphics& gfx, VecI pos,int width, int height) const
	{
		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
	}
private:
	std::unordered_set<std::shared_ptr<T>> observers;
	Color c = Colors::Blue;
};

typedef _Tile<IGui> Tile;