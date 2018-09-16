#pragma once
#include <assert.h>
#include "Graphics.h"
#include "Rect.h"
#include "Mouse.h"
class MenuItem
{
public:
	virtual void Draw(Graphics& gfx) const {};
	virtual void Update(float dt, Mouse& mouse) = 0;
	virtual void MouseLeave() {};
	virtual void MouseIn(Mouse& mouse) {};
	virtual void ResetState() {};
	inline RectF GetRect() noexcept
	{
		return RectF(pos, width, height);
	}
	inline VecF GetPos() noexcept
	{
		return pos;
	}
	inline float GetWidth() noexcept
	{
		return width;
	}
	inline float GetHeight() noexcept
	{
		return height;
	}
	inline void setColor(Color c)  noexcept
	{
		color = c;
		baseColor = c;
	}
	void SetSprite(const std::shared_ptr<Surface> surf)
	{
		this->surf = surf;
		offSetX = ((int)width - surf->GetWidth()) / 2;
		offSetY = ((int)height - surf->GetHeight()) / 2;
	}
protected:
	MenuItem(VecF pos, float width, float height)
		:
		pos(pos),
		width(width),
		height(height)
	{}
	VecF pos;
	float width;
	float height;
	int offSetX = 0;
	int offSetY = 0;
	Color color;
	Color baseColor;
	std::shared_ptr<Surface> surf;
};