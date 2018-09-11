#pragma once
#include <functional>
#include <map>
#include "MenuItem.h"
#include "ButtonState.h"
class Button : public MenuItem
{
public:
	Button(VecF pos, float width, float height)
		:
		MenuItem(pos, width, height)
	{}
	void Draw(Graphics& gfx) const override;
	void Update(float dt, Mouse& mouse) override;
	void MouseIn(Mouse& mouse) override;
	void MouseLeave() override;
	void ResetState() override;
	void AddEventListener(Mouse::Event::Type type, std::function<void()> pFunc)
	{
		handlers.emplace(type, pFunc);
	}
private:
	friend BtnClickState;
	friend BtnSleepState;
	friend BtnMouseHoverState;
	BtnClickState clickedState;
	BtnSleepState sleepState;
	BtnMouseHoverState hoverState;
	ButtonState* btnState = &sleepState;
	std::map<Mouse::Event::Type, std::function<void()>> handlers;
	float timer = 0.0f;
};