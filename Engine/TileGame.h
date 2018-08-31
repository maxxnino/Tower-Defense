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
	inline void Awake() noexcept
	{
		isAwake = true;
	}
	inline void Sleep() noexcept
	{
		isAwake = false;
	}
	virtual void Draw(Graphics& gfx, VecI pos, int width, int height) const noexcept = 0;
	virtual void UpgradeTower(const TypeDame* typeDame) = 0;
protected:
	bool isAwake = false;
};