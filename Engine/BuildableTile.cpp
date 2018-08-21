#include "BuildableTile.h"
#include "Button.h"
#include "MouseState.h"
void BuildableTile::Draw(Graphics & gfx, VecI pos, int width, int height, IObervable * obs) const
{
	if (isAwake)
	{
		auto typeDame = static_cast<MouseState*>(obs)->typeDame;
		if (typeDame == nullptr)
		{
			if (myTower != nullptr)
			{
				gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, myTower->GetColor());
			}
			else
			{
				gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
			}
		}
		else
		{
			gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, typeDame->getColor());
		}
	}
	else
	{
		if (myTower)
		{
			gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, myTower->GetColor());
		}
		else
		{
			gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
		}
	}
}

void BuildableTile::MouseClick(const VecI & mousePos, IObervable * obs)
{
	auto newType = static_cast<MouseState*>(obs)->typeDame;
	if (newType == nullptr)
	{
		if (myTower != nullptr)
		{
			Notify(this);
		}
	}
	else
	{
		if (myTower == nullptr)
		{
			myTower = std::make_shared<Tower>(Colors::Red);
			myTower->Upgrade(newType);
		}
	}
}

void BuildableTile::OnNotify(Observer * userData)
{
	myTower->Upgrade(static_cast<Button*>(userData)->getData());
}

void BuildableTile::AddEntity(std::shared_ptr<Tower> tower)
{
	myTower = tower;
}
