#include "BuildableTile.h"
#include "Button.h"
#include "MouseState.h"
void BuildableTile::Draw(Graphics & gfx, VecI pos, int width, int height, IObervable * obs) const noexcept
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

void BuildableTile::MouseClick(const VecI & mousePos, IObervable * obs) noexcept
{
	auto data = static_cast<MouseState*>(obs)->typeDame;
	if (!data)
	{
		if (!myTower)
		{
			//that mean nothing in mouse, and this tile have tower, clicked for open upgrade menu from Menumanager
			Notify(this);
		}
	}
	else
	{
		// have data, delete or build tower base on IItemData 
		data->executed(this);
	}
}

void BuildableTile::OnNotify(Observer * userData)
{
	// call from Menumanager when one Button from upgrade menu clicked
	auto data = static_cast<Button*>(userData)->getData();
	myTower->Upgrade(static_cast<TypeDame*>(data));
}

void BuildableTile::AddEntity(std::shared_ptr<Tower> tower)
{
	myTower = tower;
}

void BuildableTile::BuildTower(TypeDame * type)
{
	if (!myTower)
	{
		myTower = std::make_shared<Tower>(Colors::Red);
		myTower->Upgrade(type);
	}
}
