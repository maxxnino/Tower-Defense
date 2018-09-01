#pragma once
#include "TileGame.h"

class WalkableTile : public TileGame
{
public:
	void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept override {};
	void MouseClick(const VecI& mousePos, IMediator* mediator) override {};
private:
	static constexpr Color c = Colors::Blue;
};