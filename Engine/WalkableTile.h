#pragma once
#include "TileGame.h"

class WalkableTile : public TileGame
{
public:
	void Draw(Graphics& gfx, VecI pos, int width, int height, IObervable* obs) const override
	{
		if (isAwake)
		{
			auto typeDame = static_cast<MouseState*>(obs)->typeDame;
			if (typeDame == nullptr)
			{
				
			}
			else
			{
				gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, typeDame->getColor());
			}
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