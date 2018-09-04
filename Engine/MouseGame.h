#pragma once
#include "Element.h"
#include "ElementFactory.h"
class MouseGame
{
public:
	
	Element* getElement()
	{
		return element;
	}
	inline void Clear() noexcept
	{
		element = nullptr;
	}
	inline void ChangeToFire() noexcept
	{
		element = &fire;
	}
	inline void ChangeToIce() noexcept
	{
		element = &ice;
	}
	inline void ChangeToLighting() noexcept
	{
		element = &lighting;
	}
	inline const Color& GetFireColor() const noexcept
	{
		return fire.getColor();
	}
	inline const Color& GetIceColor() const noexcept
	{
		return ice.getColor();
	}
	inline const Color& GetLightingColor() const noexcept
	{
		return lighting.getColor();
	}
	inline int GetGold() const
	{
		assert(element);
		return element->GetGold();
	}
private:
	Element* element = nullptr;
	Fire fire;
	Ice ice;
	Lighting lighting;
	ElementFactory factory;
};