#pragma once
#include <unordered_set>
#include <algorithm>
#include "IObservable.h"
class Observer
{
public:
	void AddObs(IObervable* obs)
	{
		observable.emplace(obs);
	}
	void RemoveObs(IObervable* obs)
	{
		observable.erase(obs);
	}
	void Notify(void* userData)
	{
		std::for_each(observable.begin(), observable.end(), [userData](auto o) {o->OnNotify(userData); });
	}
	void Clear()
	{
		observable.clear();
	}
private:
	std::unordered_set<IObervable*> observable;
};