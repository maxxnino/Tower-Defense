#include "Button.h"

void Button::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim((VecI)pos, (int)width, (int)height, color);
}

void Button::ProccessCommand(Mouse & mouse)
{
}

void Button::Update(float dt)
{
	btnState->Update(dt, this);
}

void Button::OnNotify()
{
	btnState->WakeUp(this);
}
