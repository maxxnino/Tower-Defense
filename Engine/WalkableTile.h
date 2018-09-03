#pragma once
#include "TileGame.h"
class WalkableTile : public TileGame
{
public:
	WalkableTile(VecI pos, int tileIndex, const Surface* surf)
		:
		pos(pos),
		tileIndex(tileIndex),
		surf(surf)
	{}
	void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept override
	{
		//gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, defaultColor);
		gfx.DrawSprite(pos.x, pos.y, *surf, SpriteEffect::Copy{});
	}
private:
	const Surface* surf;
	const int tileIndex;
	VecI pos;
};