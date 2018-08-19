#pragma once
#include "Observer.h"
#include "MenuItem.h"
class MouseState : public IObervable
{
public:
	void OnNotify(void* datauser) override
	{
		data = static_cast<MenuItem*>(datauser)->getData();
	}
	int data = 0;
};