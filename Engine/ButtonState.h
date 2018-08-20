#pragma once
#include "Mouse.h"
template<class Data>
class Button<Data>;

class ButtonState
{
public:
	virtual void Update(float dt, Button<Data>* btn, Mouse& mouse) = 0;
	virtual void Reset(Button<Data>* btn) = 0;
	virtual void MouseLeave(Button<Data>* btn) = 0;
	virtual void MouseIn(Button<Data>* btn, Mouse& mouse) = 0;
};
class BtnClickState : public ButtonState
{
public:
	void Update(float dt, Button<Data>* btn, Mouse& mouse) override;
	void Reset(Button<Data>* btn) override;
	void MouseLeave(Button<Data>* btn) override {}
	void MouseIn(Button<Data>* btn, Mouse& mouse) override {}
};
class BtnSleepState : public ButtonState
{
public:
	void Update(float dt, Button<Data>* btn, Mouse& mouse) override {}
	void Reset(Button* btn) override {}
	void MouseLeave(Button* btn) override {}
	void MouseIn(Button* btn, Mouse& mouse) override;
};
class BtnMouseHoverState : public ButtonState
{
public:
	void Update(float dt, Button* btn, Mouse& mouse) override {}
	void Reset(Button* btn) override;
	void MouseLeave(Button* btn) override;
	void MouseIn(Button* btn, Mouse& mouse) override;
};