#pragma once
#include "IObservable.h"
#include "TypeDame.h"
class MouseState : public IObervable
{
public:
	void OnNotify(Observer* datauser) override;
	TypeDame* typeDame = nullptr;
	FireDame fire;
	IceDame ice;
	LightingDame lighting;
};