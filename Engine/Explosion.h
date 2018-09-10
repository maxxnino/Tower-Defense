#pragma once
#include "Animation.h"
class Explosion
{
public:
	Explosion(const Animation* animation,VecI pos)
		:
		animation(animation),
		pos(pos)
	{}
	void Draw(Graphics& gfx)
	{
		animation->DrawAlpha(pos, gfx, iCurFrame);
	}
	bool Update(float dt)
	{
		curFrameTime += dt;
		while (curFrameTime >= holdTime)
		{
			if (++iCurFrame >= animation->GetNFrames())
			{
				return true;
			}
			curFrameTime -= holdTime;
		}
		return false;
	}
private:
	const Animation* animation;
	VecI pos;
	int iCurFrame = 0;
	float holdTime;
	float curFrameTime = 0.0f;
};