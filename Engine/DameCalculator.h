#pragma once
#include <unordered_map>
#include <functional>
#include "Attribute.h"
class DameCalculator
{
public:
	DameCalculator()
	{
		dameCalculator.emplace(Element::Fire, [this](float value, Attribute& att) {
			const float resisValue = 1.0f - (att.fireResistant + att.mFireResistant) / 100.0f;
			return value * resisValue;
		});
		dameCalculator.emplace(Element::Water, [this](float value, Attribute& att) {
			const float resisValue = 1.0f - (att.waterResistant + att.mWaterResistant) / 100.0f;
			return value * resisValue;
		});
		dameCalculator.emplace(Element::Nature, [this](float value, Attribute& att) {
			const float resisValue = 1.0f - (att.natureResistant + att.mNatureResistant) / 100.0f;
			return value * resisValue;
		});


		dameCalculator.emplace(Element::Fire + Element::Fire, [this](float value, Attribute& att) {
			const float resisValue = 1.0f - (att.fireResistant + att.mFireResistant) / 100.0f;
			return value * resisValue;
		});
		dameCalculator.emplace(Element::Water + Element::Water, [this](float value, Attribute& att) {
			const float resisValue = 1.0f - (att.waterResistant + att.mWaterResistant) / 100.0f;
			return value * resisValue;
		});
		dameCalculator.emplace(Element::Nature + Element::Nature, [this](float value, Attribute& att) {
			const float resisValue = 1.0f - (att.natureResistant + att.mNatureResistant) / 100.0f;
			return value * resisValue;
		});


		dameCalculator.emplace(Element::Fire + Element::Water, [this](float value, Attribute& att) {
			const float resisValue = 1.0f - (att.fireResistant + att.mFireResistant + att.waterResistant + att.mWaterResistant) / 200.0f;
			return value * resisValue;
		});
		dameCalculator.emplace(Element::Fire + Element::Nature, [this](float value, Attribute& att) {
			const float resisValue = 1.0f - (att.fireResistant + att.mFireResistant + att.natureResistant + att.mNatureResistant) / 200.0f;
			return value * resisValue;
		});
		dameCalculator.emplace(Element::Water + Element::Nature, [this](float value, Attribute& att) {
			const float resisValue = 1.0f - (att.waterResistant + att.mWaterResistant + att.natureResistant + att.mNatureResistant) / 200.0f;
			return value * resisValue;
		});
	}

public:
	static float GetDame(int type, float value, Attribute& att)
	{
		return Get().dameCalculator.at(type)(value, att);
	}
private:
	static DameCalculator& Get()
	{
		static DameCalculator cal;
		return cal;
	}
private:
	std::unordered_map<int, std::function<float(float, Attribute&)>> dameCalculator;
};