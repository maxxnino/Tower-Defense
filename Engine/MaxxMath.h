#pragma once
#include "Vec2.h"
#include "Box2D/Common/b2Math.h"

inline VecI ConvertToScreenPos(const b2Vec2& worldPos, float scalePixel, float coordinateOffsetX, float coordinateOffsetY)
{
	return { int(worldPos.x * scalePixel + coordinateOffsetX), -int(worldPos.y * scalePixel - coordinateOffsetY) };
}
inline b2Vec2 ConvertToWorldPos(const VecF& screenPos, float scalePixel, float coordinateOffsetX, float coordinateOffsetY)
{
	return { (screenPos.x - coordinateOffsetX) / scalePixel ,(coordinateOffsetY - screenPos.y) / scalePixel };
}