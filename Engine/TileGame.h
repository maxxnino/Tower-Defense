#pragma once
#include <vector>
#include <memory>
#include "Vec2.h"
#include "Graphics.h"
#include "Tower.h"
#include "IMediator.h"
#include "TypeDame.h"
#include "Codex.h"
class TileGame
{
public:
	virtual void MouseClick(const VecI& mousePos, IMediator* mediator) {}
	virtual void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept {}
	virtual void RemoveTowerIndex() {}
	void DrawActive(Graphics& gfx, VecI pos, int width, int height, const Color& c) const
	{
		gfx.DrawRectDim(pos, width , height , c);
	}
};