#pragma once
#include <set>
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
		if (observable.size() != 0)
		{
			observable.erase(obs);
		}
	}
	void Notify(Observer * obs)
	{
		std::for_each(observable.begin(), observable.end(), [obs](auto o) {o->OnNotify(obs);});
	}
	void Clear()
	{
		observable.clear();
	}
private:
	std::set<IObervable*> observable;
};