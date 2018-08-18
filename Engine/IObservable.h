#pragma once
class IObervable
{
public:
	virtual void OnNotify(void* datauser) = 0;
};