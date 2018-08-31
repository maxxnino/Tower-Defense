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
			btn->color = btn->baseColor;
			btn->btnState = &btn->sleepState;
		}
	}
}

void BtnClickState::Reset(Button* btn)
{
	btn->timer = 0.0f;
	btn->color = btn->baseColor;
	btn->btnState = &btn->sleepState;
}

void BtnSleepState::MouseIn(Button * btn, Mouse& mouse)
{
	bool isclicked = true;
	while (!mouse.IsEmpty())
	{
		auto e = mouse.Read().GetType();
		if (e == Mouse::Event::Type::LPress)
		{
			isclicked = false;
			
			btn->color = Colors::Magenta;
			btn->btnState = &btn->clickedState;
		}
		else if (e == Mouse::Event::Type::RPress)
		{
			btn->RightClickFunc();
		}
	}
	if (isclicked)
	{
		btn->color = Colors::Yellow;
		btn->btnState = &btn->hoverState;
	}
	else
	{
		btn->LeftClickFunc();
	}
}

void BtnMouseHoverState::Reset(Button* btn)
{
	MouseLeave(btn);
}

void BtnMouseHoverState::MouseLeave(Button * btn)
{
	btn->color = btn->baseColor;
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
			isclicked = false;
			btn->color = Colors::Magenta;
			btn->btnState = &btn->clickedState;
		}
		else if(e == Mouse::Event::Type::RPress)
		{
			btn->RightClickFunc();
		}
	}
	if (isclicked)
	{
		btn->color = Colors::Yellow;
		btn->btnState = &btn->hoverState;
	}
	else
	{
		btn->LeftClickFunc();
	}
}
