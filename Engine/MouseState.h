#pragma once
#include "Observer.h"
#include "MenuItem.h"
#include "Tower.h"
class MouseState : public IObervable
{
public:
	void OnNotify(Observer* datauser) override
	{
		auto btn = static_cast<MenuItem*>(datauser);
		typeDame = static_cast<TypeDame*>(btn->getData());
	}
	TypeDame* typeDame = nullptr;
	FireDame fire;
	IceDame ice;
	LightingDame lighting;
};