#pragma once
#include "TileGame.h"

class WalkableTile : public TileGame
{
public:
	void Draw(Graphics& gfx, VecI pos, int width, int height, IObervable* obs) const noexcept override;
	void MouseClick(const VecI& mousePos, IObervable* obs) noexcept override {};
	void AddEntity(std::shared_ptr<Tower>) override {};
private:
	static constexpr Color c = Colors::Blue;
};