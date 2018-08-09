#include "Button.h"

void Button::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim((VecI)pos, (int)width, (int)height, color);
}

void Button::Update(float dt, Mouse& mouse)
{
	btnState->Update(dt, this, mouse);
}

void Button::MouseClick()
{
	btnState->MouseClick(this);
}

void Button::MouseLeave()
{
	btnState->MouseLeave(this);
}

void Button::MouseIn()
{
	btnState->MouseIn(this);
}
