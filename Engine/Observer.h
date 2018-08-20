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
	void Notify(Observer * obs)
	{
		std::for_each(observable.begin(), observable.end(), [obs](auto o) {o->OnNotify(obs); });
	}
	void Clear()
	{
		observable.clear();
	}
private:
	std::unordered_set<IObervable*> observable;
};