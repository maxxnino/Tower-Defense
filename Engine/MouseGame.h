#pragma once
#include "Element.h"
#include "ElementFactory.h"
class MouseGame
{
public:
	MouseGame()
	{
		
	}
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
		element = elementFactory.MakeElement(Element::Type::Fire);
	}
	inline void ChangeToIce() noexcept
	{
		element = elementFactory.MakeElement(Element::Type::Water);
	}
	inline void ChangeToLighting() noexcept
	{
		element = elementFactory.MakeElement(Element::Type::Nature);
	}
	Color GetFireColor() noexcept
	{
		return elementFactory.MakeElement(Element::Type::Fire)->getColor();
	}
	Color GetIceColor() noexcept
	{
		return elementFactory.MakeElement(Element::Type::Water)->getColor();;
	}
	Color GetLightingColor() noexcept
	{
		return elementFactory.MakeElement(Element::Type::Nature)->getColor();;
	}
	inline int GetGold() const
	{
		assert(element);
		return element->GetGold();
	}
	Element* MakeElement(Element* a, Element* b)
	{
		return elementFactory.MakeElement(a->getType() + b->getType());
	}
private:
	Element* element = nullptr;
	ElementFactory elementFactory;
};