#pragma once
class Button;

class ButtonState
{
public:
	virtual void Update(float dt, Button* btn) = 0;
	virtual void WakeUp(Button* btn) = 0;
};
class OnClickState : public ButtonState
{
public:
	void Update(float dt, Button* btn) override;
	void WakeUp(Button* btn) override;
};
class SleepState : public ButtonState
{
public:
	void Update(float dt, Button* btn) override;
	void WakeUp(Button* btn) override;
};