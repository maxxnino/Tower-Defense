#pragma once
#include <unordered_map>
#include <functional>
#include "Attribute.h"
#include "ChiliMath.h"
class DameCalculator
{
public:
	DameCalculator()
	{
		dameCalculator.emplace(Element::Fire, [this](const float value, const Attribute& att) {
			return value * DameMultiply(att.GetTotalResistant(Element::Fire));
		});
		dameCalculator.emplace(Element::Water, [this](const float value, const Attribute& att) {
			return value * DameMultiply(att.GetTotalResistant(Element::Water));
		});
		dameCalculator.emplace(Element::Nature, [this](const float value, const Attribute& att) {
			return value * DameMultiply(att.GetTotalResistant(Element::Nature));
		});


		dameCalculator.emplace(Element::Fire + Element::Fire, [this](const float value, const Attribute& att) {
			return value * DameMultiply(att.GetTotalResistant(Element::Fire));
		});
		dameCalculator.emplace(Element::Water + Element::Water, [this](const float value, const Attribute& att) {
			return value * DameMultiply(att.GetTotalResistant(Element::Water));
		});
		dameCalculator.emplace(Element::Nature + Element::Nature, [this](const float value, const Attribute& att) {
			return value * DameMultiply(att.GetTotalResistant(Element::Nature));
		});


		dameCalculator.emplace(Element::Fire + Element::Water, [this](const float value, const Attribute& att) {
			return value * (DameMultiply(att.GetTotalResistant(Element::Fire)) + DameMultiply(att.GetTotalResistant(Element::Water))) / 2;
		});
		dameCalculator.emplace(Element::Fire + Element::Nature, [this](const float value, const Attribute& att) {
			return value * (DameMultiply(att.GetTotalResistant(Element::Fire)) + DameMultiply(att.GetTotalResistant(Element::Nature))) / 2;
		});
		dameCalculator.emplace(Element::Water + Element::Nature, [this](const float value, const Attribute& att) {
			return value * (DameMultiply(att.GetTotalResistant(Element::Water)) + DameMultiply(att.GetTotalResistant(Element::Nature))) / 2;
		});
	}
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
	std::unordered_map<int, std::function<float(const float, const Attribute&)>> dameCalculator;
};