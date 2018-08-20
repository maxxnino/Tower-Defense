#pragma once
#include "MenuItem.h"
#include "ButtonState.h"
template <class Data>
class Button : public MenuItem<Data>
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
private:
	friend BtnClickState;
	friend BtnSleepState;
	friend BtnMouseHoverState;
	BtnClickState clickedState;
	BtnSleepState sleepState;
	BtnMouseHoverState hoverState;
	ButtonState* btnState = &sleepState;
	float timer = 0.0f;
};