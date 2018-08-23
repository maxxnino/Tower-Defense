#pragma once
#include "Rect.h"
#include <algorithm>
class CollisionRect
{
public:
	CollisionRect(VecF pos, float width, float height, float maxSpeed)
		:
		pos(pos),
		width(width),
		height(height),
		maxSpeedSq(maxSpeed)
	{}
	inline RectF getRect() noexcept
	{
		return { pos, width, height };
	}
	void Update(float dt) noexcept
	{
		pos += vel * dt;
	}
	void ApplyForce(const VecF& force)
	{
		vel += force;
		const float curSpeedSq = vel.x * vel.x + vel.y * vel.y;
		if (curSpeedSq > maxSpeedSq)
		{
			float factor = std::sqrt(maxSpeedSq / curSpeedSq);
			vel *= factor;
		}
	}
private:
	VecF pos;
	VecF vel;
	float maxSpeedSq;
	float width;
	float height;
};