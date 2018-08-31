#pragma once
#include "TileGame.h"

class WalkableTile : public TileGame
{
public:
	void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept override;
	void MouseClick(const VecI& mousePos, IMediator* mediator) override {};
	void AddEntity(std::shared_ptr<Tower>) override {};
	void UpgradeTower(TypeDame* typeDame) override {};
private:
	static constexpr Color c = Colors::Blue;
};