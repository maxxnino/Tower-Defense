#pragma once
#include <vector>
#include <memory>
#include "Vec2.h"
#include "Graphics.h"
#include "Tower.h"
#include "IMediator.h"
#include "Element.h"
#include "Codex.h"
class TileGame
{
public:
	virtual void MouseClick(const VecI& mousePos, IMediator* mediator) {}
	virtual bool MouseNoneClick(IMediator* mediator) { return true; }
	virtual void MouseBuildTowerClick(IMediator* mediator) {}
	virtual void MouseDeleteTowerClick(IMediator* mediator) {}
	virtual void MouseSwapTowerClick(IMediator* mediator) {}
	virtual void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept {}
	virtual void RemoveTowerIndex() {}
	virtual int GetTileData() const = 0;
};