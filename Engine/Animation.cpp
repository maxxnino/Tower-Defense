#include "Animation.h"
#include "SpriteEffect.h"

Animation::Animation(int x, int y, int width, int height, int count,
	const Surface* sprite, float holdTime, Color chroma)
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

void Animation::Draw(const VecI& pos, Graphics& gfx, bool mirrored) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
		SpriteEffect::Chroma{ chroma }, mirrored);
}

void Animation::DrawColor(const VecI& pos, Graphics& gfx, Color c, bool mirrored) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
		SpriteEffect::Substitution{ chroma,c }, mirrored);
}

void Animation::DrawAlpha(const VecI & pos, Graphics & gfx, bool mirrored) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
		SpriteEffect::AlphaBlendBaked{}, mirrored);
}

void Animation::Update(float dt)
{
	curFrameTime += dt;
	while (curFrameTime >= holdTime)
	{
		Advance();
		curFrameTime -= holdTime;
	}
}

void Animation::Advance()
{
	if (++iCurFrame >= frames.size())
	{
		iCurFrame = 0;
	}
}