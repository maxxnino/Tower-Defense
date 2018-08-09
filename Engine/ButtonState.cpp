#include "ButtonState.h"
#include "Button.h"

void BtnClickState::Update(float dt, Button * btn, Mouse& mouse)
{
	btn->timer += dt;
	if (btn->timer >= 1.0f)
	{
		btn->timer = 0.0f;
		if (btn->GetRect().isContaint(mouse.GetPos()))
		{
			btn->color = Colors::Yellow;
			btn->btnState = &btn->hoverState;
		}
		else
		{
			btn->color = Colors::Red;
			btn->btnState = &btn->sleepState;
		}
	}
}

void BtnSleepState::MouseIn(Button * btn)
{
	btn->color = Colors::Yellow;
	btn->btnState = &btn->hoverState;
}

void BtnMouseHoverState::MouseClick(Button * btn)
{
	btn->color = Colors::Green;
	btn->btnState = &btn->clickedState;
}

void BtnMouseHoverState::MouseLeave(Button * btn)
{
	btn->color = Colors::Red;
	btn->btnState = &btn->sleepState;
}
