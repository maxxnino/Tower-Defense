#pragma once
class IObervable
{
public:
	virtual void OnNotify(class Observer* obs) = 0;
};