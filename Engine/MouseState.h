#pragma once
#include "IObservable.h"
#include "TypeDame.h"
#include "DeleteTower.h"
#include "IDataItem.h"
class MouseState : public IObervable
{
public:
	void OnNotify(Observer* datauser) override;
	IDataItem* typeDame = nullptr;
	FireDame fire;
	IceDame ice;
	LightingDame lighting;
	DeleteTower deleteTower;
};