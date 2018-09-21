#pragma once
#include "Vec2.h"
#include <algorithm>
template <typename T>
class Rect_
{
public:
	Rect_<T>() = default;
	Rect_<T>(T left, T top, T right, T bottom)
		:
		left(left),
		top(top),
		right(right),
		bottom(bottom)
	{}

	Rect_<T>(const Vec2_<T> & topleft, const Vec2_<T> & bottomright)
		:
		Rect_<T>(topleft.x, topleft.y, bottomright.x, bottomright.y)
	{}

	Rect_<T>(const Vec2_<T> & topleft, T width, T height)
		:
		Rect_<T>(topleft, topleft + Vec2_<T>(width, height))
	{}
	template<typename S>
	explicit Rect_(const Rect_<S>& src)
		:
		left((T)src.left),
		right((T)src.right),
		top((T)src.top),
		bottom((T)src.bottom)
	{}
	Rect_<T> GetRectCenter(const Vec2_<T> & center, T halfwidth, T halfheight)
	{
		Vec2_<T> half = Vec2_<T>(halfwidth, halfheight);
		return Rect_<T>(center - half, center + half);
	}

	bool IsContainedBy(const Rect_& other) const
	{
		return left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom;
	}
	bool isContaint(Vec2_<T> pos)
	{
		return pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom;
	}
	bool isOverLap(const Rect_<T> & rect) const
	{
		return left < rect.right
			&& right > rect.left
			&& bottom > rect.top
			&& top < rect.bottom;
	}
	// degenerate means top is below or equal bottom / left is right of or equal right
	bool IsDegenerate() const
	{
		return right <= left || bottom <= top;
	}
	Rect_& ClipTo(const Rect_& clip)
	{
		left = std::max(left, clip.left);
		right = std::min(right, clip.right);
		top = std::max(top, clip.top);
		bottom = std::min(bottom, clip.bottom);
		return *this;
	}
	Rect_ GetClippedTo(const Rect_& clip) const
	{
		return Rect_(*this).ClipTo(clip);
	}
	static Rect_ FromCenter(const Vec2_<T>& center, T halfWidth, T halfHeight)
	{
		const Vec2_<T> half(halfWidth, halfHeight);
		return Rect_(center - half, center + half);
	}
	Rect_ GetExpanded(T offset) const
	{
		return Rect_(left - offset, top - offset, right + offset, bottom + offset);
	}
	Vec2_<T> GetCenter() const
	{
		return Vec2_<T>((left + right) / (T)2, (top + bottom) / (T)2);
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}
	Vec2_<T> TopLeft() const
	{
		return{ left,top };
	}
	Vec2_<T> BottomRight() const
	{
		return{ right,bottom };
	}
	Rect_& DisplaceBy(const Vec2_<T>& d)
	{
		left += d.x;
		right += d.x;
		top += d.y;
		bottom += d.y;
		return *this;
	}
	Rect_ GetDisplacedBy(const Vec2_<T>& d) const
	{
		return Rect_(*this).DisplaceBy(d);
	}

public:
	T left;
	T right;
	T top;
	T bottom;
};
typedef Rect_<int> RectI;
typedef Rect_<float> RectF;
