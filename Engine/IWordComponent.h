#pragma once
#include "IWorldMediator.h"
class IWorldComponent
{
public:
	virtual void AddMediator(IWorldMediator* wordMediator) = 0;
};