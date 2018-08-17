#pragma once
class Listener
{
public:
	virtual void OnClick(void* userdata) = 0;
	int getData()
	{
		return data;
	}
protected:
	int data = 0;
};


class ButtonListener : public Listener
{
public:
	void OnClick(void* userdata) override;
	
};