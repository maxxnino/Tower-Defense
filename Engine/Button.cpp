#include "Button.h"

void Button::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim((VecI)pos, (int)width, (int)height, color);
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
