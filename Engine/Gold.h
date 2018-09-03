#pragma once
#include <assert.h>
class Gold
{
public:
	void AddGold(int amount) noexcept
	{
		assert(amount > 0);
		totalGold += amount;
	}
	void RemoveGold(int amount) noexcept
	{
		assert(amount > 0 || totalGold > amount);
		totalGold -= amount;
	}
	inline int GetGold() noexcept
	{
		return totalGold;
	}
private:
	int totalGold = 0;
};