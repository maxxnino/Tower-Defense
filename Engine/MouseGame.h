#pragma once
#include "Element.h"
#include "BuilderMatching.h"
class MouseGame
{
public:
	MouseGame()
	{
		builder.Case<Fire, Ice>([this](Element& f, Element& i)
		{
			return &fireIce;
		});
		builder.Case<Fire, Fire>([this](Element& f, Element& i)
		{
			return &fireFire;
		});
		builder.Case<Ice, Ice>([this](Element& f, Element& i)
		{
			return &iceIce;
		});
		builder.Case<Ice, Lighting>([this](Element& f, Element& i)
		{
			return &iceLight;
		});
		builder.Case<Lighting, Lighting>([this](Element& f, Element& i)
		{
			return &lightLight;
		});
		builder.Case<Fire, Lighting>([this](Element& f, Element& i)
		{
			return &fireLight;
		});
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
	Element* MakeElement(Element* a, Element* b)
	{
		return builder.Create(a, b);
	}
private:
	Element* element = nullptr;
	Fire fire;
	FireFire fireFire;
	FireIce fireIce;
	Ice ice;
	IceIce iceIce;
	IceLight iceLight;
	Lighting lighting;
	LightLight lightLight;
	FireLight fireLight;
	BuilderMatching<Element> builder;
};