#include "ButtonState.h"
#include "Button.h"
void OnClickState::Update(float dt, Button * btn)
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

void OnClickState::WakeUp(Button * btn)
{
}

void SleepState::Update(float dt, Button * btn)
{
}

void SleepState::WakeUp(Button * btn)
{
	btn->WakeUp();
}
