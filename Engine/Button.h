#pragma once
#include "IGui.h"
#include "ButtonState.h"
class Button : public IGui
{
public:
	Button(int id, VecF pos, float width, float height, Color color)
		:
		IGui(id, pos, width, height, color)
	{}
	void Draw(Graphics& gfx) const override;
	void Update(float dt) override;
	void AddItem(std::shared_ptr<IGui> item) override {}
	void OnNotify() override;
private:
	void WakeUp()
	{
		btnState = &onclickedState;
	}
	void Sleep()
	{
		btnState = &sleepState;
	}
private:
	friend OnClickState;
	friend SleepState;
	OnClickState onclickedState;
	SleepState sleepState;
	ButtonState* btnState = &sleepState;
	bool isClicked = false;
	float timer = 0.0f;
};