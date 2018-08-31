#include "BuildableTile.h"
#include "Button.h"
void BuildableTile::Draw(Graphics & gfx, VecI pos, int width, int height) const noexcept
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

void BuildableTile::MouseClick(const VecI & mousePos, IMediator* mediator) noexcept
{
	auto typeDame = mediator->GetMouseGame()->typeDame;
	if (typeDame)
	{
		if (!myTower)
		{
			BuildTower(typeDame);
		}
		else
		{
			//Todo: show message can't build tower at here
		}
	}
	else
	{
		if (myTower)
		{
			//nothing in mouse, and this tile have tower, clicked for open upgrade menu from Menumanager
			mediator->OpenUpgradeMenu(index);
		}
	}
	
}

void BuildableTile::AddEntity(std::shared_ptr<Tower> tower)
{
	myTower = tower;
}

void BuildableTile::UpgradeTower(TypeDame * typeDame)
{
	myTower->Upgrade(typeDame);
}

void BuildableTile::BuildTower(TypeDame * type)
{
	if (!myTower)
	{
		b2Vec2 worldPos = b2Vec2((float32)(pos.x - Graphics::offSetX) / (float32)Graphics::scalePixel, (float32)(Graphics::offSetY - pos.y) / (float32)Graphics::scalePixel);
		float size = 10.0f;
		myTower = std::make_shared<Tower>(Colors::Red, worldPos, size);
		myTower->Upgrade(type);
	}
}
