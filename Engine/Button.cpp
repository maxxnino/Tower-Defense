#include "Button.h"

void Button::Draw(Graphics & gfx) const
{
	const VecI intPos = (VecI)pos;
	gfx.DrawRectDim(intPos, (int)width, (int)height, color);
	if (surf != nullptr)
	{
		gfx.DrawSprite(intPos.x + offSetX, intPos.y + offSetY, *surf, SpriteEffect::AlphaBlendBaked{});
	}
}

void Button::Update(float dt, Mouse& mouse)
{
	btnState->Update(dt, this, mouse);
}

void Button::MouseLeave()
{
	btnState->MouseLeave(this);
}

void Button::ResetState()
{
	btnState->Reset(this);
}

void Button::MouseIn(Mouse& mouse)
{
	btnState->MouseIn(this, mouse);
}
