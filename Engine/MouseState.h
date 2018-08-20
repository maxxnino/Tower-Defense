#pragma once
#include "Observer.h"
#include "MenuItem.h"
#include "Tower.h"
class MouseState : public IObervable
{
public:
	void OnNotify(Observer* datauser) override
	{
		typeDame = static_cast<MenuItem*>(datauser)->getData();
	}
	TypeDame* typeDame = nullptr;
	FireDame fire;
	IceDame ice;
	LightingDame lighting;
};