#pragma once
#include <cmath>
template<typename T>
constexpr float EaseOut(T curTime, T startValue, T changeInValue, T duration) noexcept
{
	curTime /= duration / 2;
	if (curTime < 1) return changeInValue / 2 * curTime * curTime + startValue;

	curTime--;
	return -changeInValue / 2 * (curTime * (curTime - 2) - 1) + startValue;
};

//1 - (0.05 × resistant ÷ (1 + 0.05 × |resistant|))
inline float DameMultiply(float a1, float a2) noexcept
{
	return 1.0f - 0.05f * (a1 + a2) / (1.0f + 0.05f * abs(a1 + a2));
}