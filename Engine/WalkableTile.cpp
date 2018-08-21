#include "WalkableTile.h"
#include "MouseState.h"

void WalkableTile::Draw(Graphics & gfx, VecI pos, int width, int height, IObervable * obs) const
{
	if (isAwake)
	{
		auto typeDame = static_cast<MouseState*>(obs)->typeDame;
		if (typeDame == nullptr)
		{

		}
		else
		{
			gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, typeDame->getColor());
		}
	}
}
