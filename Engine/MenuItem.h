#pragma once
#include <memory>
#include <assert.h>
#include "Graphics.h"
#include "Rect.h"
#include "Mouse.h"
#include "Observer.h"
#include "TypeDame.h"
class MenuItem : public Observer, public IObervable
{
public:
	virtual void Draw(Graphics& gfx) const = 0;
	virtual void Update(float dt, Mouse& mouse) = 0;
	virtual void MouseLeave() = 0;
	virtual void MouseIn(Mouse& mouse) = 0;
	virtual void ResetState() = 0;
	void OnNotify(Observer* datauser) override {};
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
	inline TypeDame* getData() { return data; }
	inline void setData(TypeDame* newdata) { data = newdata; }
	inline void setColor(Color c)  noexcept
	{
		color = c;
		baseColor = c;
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
	Color color;
	Color baseColor;
	TypeDame* data;
private:
};