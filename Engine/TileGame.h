#pragma once
#include <vector>
#include <memory>
#include "Vec2.h"
#include "Graphics.h"
#include "Tower.h"
#include "IMediator.h"
#include "TypeDame.h"
class TileGame
{
public:
	virtual void MouseClick(const VecI& mousePos, IMediator* mediator) noexcept = 0;
	virtual void AddEntity(std::shared_ptr<Tower>) = 0;
	virtual void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept = 0;
	virtual void UpgradeTower(TypeDame* typeDame) = 0;
	void DrawActive(Graphics& gfx, VecI pos, int width, int height, const Color& c) const
	{
		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
	}
};