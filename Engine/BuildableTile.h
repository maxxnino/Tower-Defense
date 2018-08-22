#pragma once
#include "TileGame.h"

class BuildableTile : public TileGame
{
public:
	void Draw(Graphics& gfx, VecI pos, int width, int height, IObervable* obs) const noexcept override;
	void MouseClick(const VecI& mousePos, IObervable* obs) noexcept override;
	void OnNotify(Observer* userData) override;
	void AddEntity(std::shared_ptr<Tower> tower) override;
	void DeleteTower()
	{
		myTower.reset();
	}
	void BuildTower(TypeDame* type);
private:
	static constexpr Color c = Colors::Gray;
	std::shared_ptr<Tower> myTower;
};