#pragma once
#include "IGui.h"
#include "ButtonState.h"
class Button : public IGui
{
public:
	Button(VecF pos, float width, float height, Color color)
		:
		IGui(pos, width, height, color)
	{}
	void Draw(Graphics& gfx) const override;
	void Update(float dt, Mouse& mouse) override;
	void AddItem(std::shared_ptr<IGui> item) override {}
	void OnNotify() override;
private:
	void WakeUp()
	{
		btnState = &clickedState;
	}
	void Sleep()
	{
		btnState = &sleepState;
	}
private:
	friend BtnClickState;
	friend BtnSleepState;
	BtnClickState clickedState;
	BtnSleepState sleepState;
	ButtonState* btnState = &sleepState;
	bool isClicked = false;
	float timer = 0.0f;
};