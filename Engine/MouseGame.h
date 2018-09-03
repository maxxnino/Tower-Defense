#pragma once
#include "TypeDame.h"

class MouseGame
{
public:
	
	TypeDame* getTypeDame()
	{
		return typeDame;
	}
	inline void Clear() noexcept
	{
		typeDame = nullptr;
	}
	inline void ChangeToFire() noexcept
	{
		typeDame = &fire;
	}
	inline void ChangeToIce() noexcept
	{
		typeDame = &ice;
	}
	inline void ChangeToLighting() noexcept
	{
		typeDame = &lighting;
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
		assert(typeDame);
		return typeDame->GetGold();
	}
private:
	TypeDame * typeDame = nullptr;
	FireDame fire;
	IceDame ice;
	LightingDame lighting;
};