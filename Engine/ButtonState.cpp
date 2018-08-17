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

void BtnSleepState::MouseIn(Button * btn, Mouse& mouse)
{
	bool isclicked = true;
	while (!mouse.IsEmpty())
	{
		auto e = mouse.Read().GetType();
		if (e == Mouse::Event::Type::LPress)
		{
			btn->listener->OnClick(btn);
			isclicked = false;
			btn->color = Colors::Green;
			btn->btnState = &btn->clickedState;
		}
	}
	if (isclicked)
	{
		btn->color = Colors::Yellow;
		btn->btnState = &btn->hoverState;
	}
}

void BtnMouseHoverState::MouseLeave(Button * btn)
{
	btn->color = Colors::Red;
	btn->btnState = &btn->sleepState;
}

void BtnMouseHoverState::MouseIn(Button * btn, Mouse & mouse)
{
	bool isclicked = true;
	while (!mouse.IsEmpty())
	{
		auto e = mouse.Read().GetType();
		if (e == Mouse::Event::Type::LPress)
		{
			btn->listener->OnClick(btn);
			isclicked = false;
			btn->color = Colors::Green;
			btn->btnState = &btn->clickedState;
		}
	}
	if (isclicked)
	{
		btn->color = Colors::Yellow;
		btn->btnState = &btn->hoverState;
	}
}
