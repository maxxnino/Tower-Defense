#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
#include <memory>
class ISpell
{
public:
	virtual void Update(float dt, PhysicObject& entity) = 0;
	virtual void Draw(Graphics& gfx, const VecI& pos) const = 0;
	virtual void EntityChangeData(PhysicObject& entity) = 0;
	virtual bool GetIsRemove() const = 0;
	virtual std::unique_ptr<ISpell> Clone() const = 0;
};