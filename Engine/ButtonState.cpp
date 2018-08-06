#include "ButtonState.h"
#include "Button.h"
void BtnClickState::Update(float dt, Button * btn)
{
	btn->color = Colors::Green;
	btn->timer += dt;
	if (btn->timer >= 1.0f)
	{
		btn->timer = 0.0f;
		btn->color = Colors::Red;
		btn->Sleep();	
	}
}

void BtnClickState::WakeUp(Button * btn)
{
}

void BtnSleepState::Update(float dt, Button * btn)
{
}

void BtnSleepState::WakeUp(Button * btn)
{
	btn->WakeUp();
}
