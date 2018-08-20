#pragma once
#include "TileGame.h"

class WalkableTile : public TileGame
{
public:
	void Draw(Graphics& gfx, VecI pos, int width, int height) const override
	{
		if (isAwake)
		{
			gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
		}
	}
	void MouseClick(const VecI& mousePos, IObervable* obs) override {};
	void AddEntity(std::shared_ptr<Tower>) override {};
	void OnNotify(void* userData) override
	{

	}
private:
	static constexpr Color c = Colors::Blue;
};