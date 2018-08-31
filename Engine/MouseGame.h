#pragma once
#include "TypeDame.h"

class MouseGame
{
public:
	TypeDame * typeDame = nullptr;
	FireDame fire;
	IceDame ice;
	LightingDame lighting;
};