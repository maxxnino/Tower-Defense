#include "BuildableTile.h"
#include "Button.h"
#include "MouseState.h"
void BuildableTile::Draw(Graphics & gfx, VecI pos, int width, int height) const noexcept
{
	//if (isAwake)
	//{
	//	auto typeDame = static_cast<MouseState*>(obs)->typeDame;
	//	if (typeDame == nullptr)
	//	{
	//		if (myTower != nullptr)
	//		{
	//			gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, myTower->GetColor());
	//		}
	//		else
	//		{
	//			gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
	//		}
	//	}
	//	else
	//	{
	//		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, typeDame->getColor());
	//	}
	//}
	//else
	//{
	//	if (myTower)
	//	{
	//		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, myTower->GetColor());
	//	}
	//	else
	//	{
	//		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
	//	}
	//}
}

void BuildableTile::MouseClick(const VecI & mousePos) noexcept
{
	//auto data = static_cast<MouseState*>(obs)->typeDame;
	//if (!data)
	//{
	//	if (myTower)
	//	{
	//		//that mean nothing in mouse, and this tile have tower, clicked for open upgrade menu from Menumanager
	//		Notify(this);
	//	}
	//}
	//else
	//{
	//	// have data, delete or build tower base on IItemData 
	//	data->executed(this);
	//}
}

void BuildableTile::AddEntity(std::shared_ptr<Tower> tower)
{
	myTower = tower;
}

void BuildableTile::BuildTower(TypeDame * type)
{
	//call from TypeDame for build tower
	//if (!myTower)
	//{
	//	b2Vec2 worldPos = b2Vec2((float32)(pos.x - Graphics::offSetX) / (float32)Graphics::scalePixel, (float32)(Graphics::offSetY - pos.y) / (float32)Graphics::scalePixel);
	//	float size = 10.0f;
	//	myTower = std::make_shared<Tower>(type->GetBox2DEngine(),Colors::Red, worldPos, size);
	//	myTower->Upgrade(type);
	//}
}
