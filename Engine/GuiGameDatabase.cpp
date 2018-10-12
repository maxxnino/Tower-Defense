#include "GuiGameDatabase.h"
#include "IMediator.h"
void GuiGameDatabase::AddMediator(IMediator* mediator)
{
	guiMediator = mediator;
}

void GuiGameDatabase::Draw(Graphics & gfx, const Camera & cam) const
{
	const auto drawPos = cam.GetDrawPosition(pos);
	switch (state)
	{
	case None:
		break;
	case BuildTower:
		//gfx.DrawSprite(pos.x, pos.y, *element->GetElementSurface(), SpriteEffect::Ghost(Colors::Magenta));
		element->GetTowerAnimation()->DrawGhost(drawPos, gfx, 0);
		break;
	case SellTower:
		gfx.DrawSprite(drawPos.x, drawPos.y, *sellTowerSurf, SpriteEffect::AlphaBlendBakedAndGhost());
		break;
	case SwapTower:
		if (posAndTowerIndex.second != -1)
		{
			gfx.DrawSprite(drawPos.x, drawPos.y, *swapTowerSurf, SpriteEffect::AlphaBlendBakedAndGhost());
		}
		else
		{
			gfx.DrawSprite(drawPos.x, drawPos.y, *swapTowerSurf, SpriteEffect::AlphaBlendBakedAndGhost());
		}
		break;
		/*case DropItem:
			break;
		default:
			break;*/
	}
}
