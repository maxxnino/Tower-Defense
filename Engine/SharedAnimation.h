#pragma once
#include "Surface.h"
#include "Graphics.h"
#include <vector>

class SharedAnimationData
{
public:
	SharedAnimationData(int x, int y, int width, int height, int count, const std::shared_ptr<Surface> sprite, float holdTime, Color chroma = Colors::Magenta)
		:
		sprite(sprite),
		holdTime(holdTime),
		chroma(chroma),
		offSet(height / 2)
	{
		for (int i = 0; i < count; i++)
		{
			frames.emplace_back(x + i * width, y, x + (i + 1) * width, y + height);
		}
	}
	void DrawGhost(const VecI& pos, Graphics& gfx, int iCurFrame, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
			SpriteEffect::AlphaBlendBakedAndGhost{}, mirrored);
	}
	void DrawGhostOffSet(const VecI& pos, Graphics& gfx, int iCurFrame, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x - offSet, pos.y - offSet, frames[iCurFrame], *sprite,
			SpriteEffect::AlphaBlendBakedAndGhost{}, mirrored);
	}
	void Draw(const VecI& pos, Graphics& gfx, int iCurFrame, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
			SpriteEffect::Chroma{ chroma }, mirrored);
	}
	void DrawOffset(const VecI& pos, Graphics& gfx, int iCurFrame, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x - offSet, pos.y - offSet, frames[iCurFrame], *sprite,
			SpriteEffect::Chroma{ chroma }, mirrored);
	}
	// this version of draw replaces all opaque pixels with specified color
	void DrawColor(const VecI& pos, Graphics& gfx, int iCurFrame, Color c, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
			SpriteEffect::Substitution{ chroma,c }, mirrored);
	}
	// this version of draw replaces all opaque pixels with specified color
	void DrawAlpha(const VecI& pos, Graphics& gfx, int iCurFrame, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], *sprite,
			SpriteEffect::AlphaBlendBaked{}, mirrored);
	}
	void DrawAlphaOffSet(const VecI& pos, Graphics& gfx, int iCurFrame, bool mirrored = false) const
	{
		gfx.DrawSprite(pos.x - offSet, pos.y - offSet, frames[iCurFrame], *sprite,
			SpriteEffect::AlphaBlendBaked{}, mirrored);
	}
	inline const int GetFrameSize() const
	{
		return (int)frames.size();
	}
	inline const float GetHoldFrame() const
	{
		return holdTime;
	}
	const std::shared_ptr<Surface> GetSurface() const
	{
		return sprite;
	}
private:
	Color chroma;
	int offSet;
	std::shared_ptr<Surface> sprite;
	std::vector<RectI> frames;
	float holdTime;
};
class SharedAnimation
{
public:
	SharedAnimation(const SharedAnimationData* data)
		:
		data(data)
	{}
	void Draw(const VecI& pos, Graphics& gfx, bool mirrored = false) const
	{
		data->Draw(pos, gfx, iCurFrame, mirrored);
	}
	void DrawOffset(const VecI& pos, Graphics& gfx, bool mirrored = false) const
	{
		data->DrawOffset(pos, gfx, iCurFrame, mirrored);
	}
	// this version of draw replaces all opaque pixels with specified color
	void DrawColor(const VecI& pos, Graphics& gfx, Color c, bool mirrored = false) const
	{
		data->DrawColor(pos, gfx, iCurFrame, mirrored);
	}
	// this version of draw replaces all opaque pixels with specified color
	void DrawAlpha(const VecI& pos, Graphics& gfx, bool mirrored = false) const
	{
		data->DrawAlpha(pos, gfx, iCurFrame, mirrored);
	}void DrawAlphaOffSet(const VecI& pos, Graphics& gfx, bool mirrored = false) const
	{
		data->DrawAlphaOffSet(pos, gfx, iCurFrame, mirrored);
	}
	void Update(float dt)
	{
		curFrameTime += dt;
		while (curFrameTime >= data->GetHoldFrame())
		{
			Advance();
			curFrameTime -= data->GetHoldFrame();
		}
	}
	const SharedAnimationData* GetAnimationData() const
	{
		return data;
	}
	void ChangeAnimation(const SharedAnimationData* newData)
	{
		data = newData;
		ResetAnimation();
	}
private:
	void ResetAnimation()
	{
		iCurFrame = 0;
		curFrameTime = 0;
	}
	void Advance()
	{
		if (++iCurFrame >= data->GetFrameSize())
		{
			iCurFrame = 0;
		}
	}
private:
	const SharedAnimationData* data;
	int iCurFrame = 0;
	float curFrameTime = 0.0f;
};

class OnetimeAnimation
{
public:
	OnetimeAnimation(const SharedAnimationData* data, const VecI& pos, bool mirrored = false)
		:
		data(data),
		pos(pos),
		mirrored(mirrored)
	{}
	void Draw(Graphics& gfx, const VecI& camPos) const
	{
		data->Draw(pos + camPos, gfx, iCurFrame);
	}
	// this version of draw replaces all opaque pixels with specified color
	void DrawColor(Graphics& gfx, Color c, const VecI& camPos) const
	{
		data->DrawColor(pos + camPos, gfx, iCurFrame, c, mirrored);
	}
	// this version of draw replaces all opaque pixels with specified color
	void DrawAlpha(Graphics& gfx, const VecI& camPos) const
	{
		data->DrawAlpha(pos + camPos, gfx, iCurFrame, mirrored);
	}
	void DrawAlphaOffSet(Graphics& gfx, const VecI& camPos) const
	{
		data->DrawAlphaOffSet(pos + camPos, gfx, iCurFrame, mirrored);
	}
	bool Update(float dt)
	{
		curFrameTime += dt;
		while (curFrameTime >= data->GetHoldFrame())
		{
			curFrameTime -= data->GetHoldFrame();
			if (++iCurFrame >= data->GetFrameSize())
			{
				return true;
			}
		}
		return false;
	}
	void ChangeAnimation(const SharedAnimationData* newData)
	{
		data = newData;
		ResetAnimation();
	}
private:
	void ResetAnimation()
	{
		iCurFrame = 0;
		curFrameTime = 0;
	}
	void Advance()
	{
		if (++iCurFrame >= data->GetFrameSize())
		{
			iCurFrame = 0;
		}
	}
private:
	const SharedAnimationData* data;
	VecI pos;
	int iCurFrame = 0;
	float curFrameTime = 0.0f;
	bool mirrored;
};