#pragma once
#include "Rect.h"
#include "Graphics.h"
#include "Box2D/Common/b2Math.h"
class Camera
{
public:
	VecF GetPos() const
	{
		return pos;
	}
	b2Vec2 GetWorldPos() const
	{
		return b2Vec2(-pos.x / scalePixel, -pos.y / scalePixel);
	}
	b2Vec2 ScreenToWorldPos(const VecF& screenPos) const
	{
		const auto newPos = VecF(screenPos.x - coordinateOffsetX - pos.x, -screenPos.y + coordinateOffsetY - pos.y);
		return b2Vec2(newPos.x / scalePixel, newPos.y / scalePixel);
	}
	void MoveBy(const VecF& offset)
	{
		pos += offset;
	}
	void MoveTo(const VecF& pos_in)
	{
		pos = pos_in;
	}
	VecI GetDrawPosition(const b2Vec2& position) const
	{
		return VecI(int(pos.x + coordinateOffsetX + position.x * scalePixel), -int(position.y * scalePixel + pos.y - coordinateOffsetY));
	}
	RectF GetViewportRect() const
	{
		return RectF(-(pos.x + coordinateOffsetX) / scalePixel, (coordinateOffsetY - pos.y) / scalePixel,
			(coordinateOffsetX - pos.x) / scalePixel, -(pos.y + coordinateOffsetY) / scalePixel);
	}
private:
	VecF pos = { 0.0f,0.0f };
public:
	static constexpr float coordinateOffsetX = float(Graphics::ScreenWidth / 2);
	static constexpr float coordinateOffsetY = float(Graphics::ScreenHeight / 2);
	static constexpr int scalePixel = 20;
};