#pragma once
#include "TileGame.h"

class BuildableTile : public TileGame
{
public:
	void Draw(Graphics& gfx, VecI pos, int width, int height, IObervable* obs) const override;
	void MouseClick(const VecI& mousePos, IObervable* obs) override;
	void OnNotify(Observer* userData) override;
	void AddEntity(std::shared_ptr<Tower> tower) override;
private:
	static constexpr Color c = Colors::Gray;
	std::shared_ptr<Tower> myTower;
};