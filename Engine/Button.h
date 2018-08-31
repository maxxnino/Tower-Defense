#pragma once
#include <functional>
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
	std::function<void()>& getFunction()
	{
		return pFunc;
	}
private:
	friend BtnClickState;
	friend BtnSleepState;
	friend BtnMouseHoverState;
	BtnClickState clickedState;
	BtnSleepState sleepState;
	BtnMouseHoverState hoverState;
	ButtonState* btnState = &sleepState;
	std::function<void()> pFunc = []() {};
	float timer = 0.0f;
};