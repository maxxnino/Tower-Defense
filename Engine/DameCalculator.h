#pragma once
#include <unordered_map>
#include <functional>
#include "Attribute.h"
class DameCalculator
{
public:
	DameCalculator()
	{
		//1 - (0.05 × resistant ÷ (1 + 0.05 × |resistant|))
		dameCalculator.emplace(Element::Fire, [this](float value, Attribute& att) {
			return value * GetValue(att.fireResistant, att.mFireResistant);
		});
		dameCalculator.emplace(Element::Water, [this](float value, Attribute& att) {
			return value * GetValue(att.waterResistant, att.mWaterResistant);
		});
		dameCalculator.emplace(Element::Nature, [this](float value, Attribute& att) {
			return value * GetValue(att.natureResistant, att.mNatureResistant);
		});


		dameCalculator.emplace(Element::Fire + Element::Fire, [this](float value, Attribute& att) {
			return value * GetValue(att.fireResistant, att.mFireResistant);
		});
		dameCalculator.emplace(Element::Water + Element::Water, [this](float value, Attribute& att) {
			return value * GetValue(att.waterResistant, att.mWaterResistant);
		});
		dameCalculator.emplace(Element::Nature + Element::Nature, [this](float value, Attribute& att) {
			return value * GetValue(att.natureResistant, att.mNatureResistant);
		});


		dameCalculator.emplace(Element::Fire + Element::Water, [this](float value, Attribute& att) {
			return value * (GetValue(att.fireResistant, att.mFireResistant) + GetValue(att.waterResistant, att.mWaterResistant)) / 2;
		});
		dameCalculator.emplace(Element::Fire + Element::Nature, [this](float value, Attribute& att) {
			return value * (GetValue(att.fireResistant, att.mFireResistant) + GetValue(att.natureResistant, att.mNatureResistant)) / 2;
		});
		dameCalculator.emplace(Element::Water + Element::Nature, [this](float value, Attribute& att) {
			return value * (GetValue(att.waterResistant, att.mWaterResistant) + GetValue(att.natureResistant, att.mNatureResistant)) / 2;
		});
	}
public:
	static float GetDame(int type, float value, Attribute& att)
	{
		return Get().dameCalculator.at(type)(value, att);
	}
private:
	constexpr float GetValue(float a1, float a2)
	{
		return 1.0f - 0.05f * (a1 + a2) / (1.0f + 0.05f * absoluteValue<float>(a1 + a2));
	}
	template <typename T>
	constexpr T absoluteValue(T x) const
	{
		return x >= 0 ? x : -x;
	}
	static DameCalculator& Get()
	{
		static DameCalculator cal;
		return cal;
	}
private:
	std::unordered_map<int, std::function<float(float, Attribute&)>> dameCalculator;
};