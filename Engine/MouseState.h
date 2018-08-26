#pragma once
#include "IObservable.h"
#include "TypeDame.h"
#include "DeleteTower.h"
#include "IDataItem.h"
#include "Box2D/Box2D.h"
class MouseState : public IObervable
{
public:
	MouseState(b2World& box2DEngine)
		:
		fire(box2DEngine),
		ice(box2DEngine),
		lighting(box2DEngine)
	{}
	void OnNotify(Observer* datauser) override;
	IDataItem* typeDame = nullptr;
	FireDame fire;
	IceDame ice;
	LightingDame lighting;
	DeleteTower deleteTower;
};