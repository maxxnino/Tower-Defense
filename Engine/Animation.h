#pragma once

#include "Surface.h"
#include "Graphics.h"
#include <vector>

class Animation
{
public:
	Animation(int x, int y, int width, int height, int count, const Surface* sprite, float holdTime, Color chroma = Colors::Magenta)
		:
		sprite(sprite),
		holdTime(holdTime),
		chroma(chroma)
	{
		for (int i = 0; i < count; i++)
		{
			frames.emplace_back(x + i * width, y, x + (i + 1) * width, y + height);
		}
	}
	void Draw(const VecI& pos, Graphics& gfx, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
			SpriteEffect::Chroma{ chroma }, mirrored);
	}
	// this version of draw replaces all opaque pixels with specified color
	void DrawColor(const VecI& pos, Graphics& gfx, Color c, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
			SpriteEffect::Substitution{ chroma,c }, mirrored);
	}
	// this version of draw replaces all opaque pixels with specified color
	void DrawAlpha(const VecI& pos, Graphics& gfx, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
			SpriteEffect::AlphaBlendBaked{}, mirrored);
	}
	void Update(float dt)
	{
		curFrameTime += dt;
		while (curFrameTime >= holdTime)
		{
			Advance();
			curFrameTime -= holdTime;
		}
	}
private:
	void Advance()
	{
		if (++iCurFrame >= frames.size())
		{
			iCurFrame = 0;
		}
	}
private:
	Color chroma;
	const Surface* sprite;
	std::vector<RectI> frames;
	int iCurFrame = 0;
	float holdTime;
	float curFrameTime = 0.0f;
};