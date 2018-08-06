#include "Button.h"

void Button::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim((VecI)pos, (int)width, (int)height, color);
}

void Button::Update(float dt, Mouse& mouse)
{
	btnState->Update(dt, this);
}

void Button::OnNotify()
{
	btnState->WakeUp(this);
}
