#pragma once
#include "TileGame.h"
class BuildableTile : public TileGame
{
public:
	BuildableTile(VecI pos,int index)
		:
		pos(pos),
		index(index)
	{}
	void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept override;
	void MouseClick(const VecI& mousePos, IMediator* mediator) noexcept override;
	void AddEntity(std::shared_ptr<Tower> tower) override;
	void UpgradeTower(TypeDame* typeDame) override;
	void DeleteTower()
	{
		myTower.reset();
	}
	void BuildTower(TypeDame* type);
private:
	static constexpr Color c = Colors::Gray;
	std::shared_ptr<Tower> myTower;
	VecI pos;
	int index;
};