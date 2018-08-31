#pragma once
#include "IMediator.h"
class IComponent
{
public:
	virtual void AddMediator(IMediator* mediator) = 0;
};