#pragma once
#include "Camera.h"
#include "Mouse.h"

class MouseCameraController
{
public:
	MouseCameraController(Mouse& mouse, Camera& cam)
		:
		mouse(mouse),
		cam(cam)
	{}
	void ProcessCommand(Mouse::Event::Type mouseEvent)
	{
		switch (mouseEvent)
		{
		case Mouse::Event::Type::LPress:
			engaged = true;
			lastPos = (VecF)mouse.GetPos();
			break;
		case Mouse::Event::Type::LRelease:
			engaged = false;
			break;
		}
	}
	void Update()
	{
		if (engaged)
		{
			const auto curPos = (VecF)mouse.GetPos();
			auto delta = lastPos - curPos;
			delta.x = -delta.x;
			cam.MoveBy(delta);
			lastPos = curPos;
		}
	}
private:
	bool engaged = false;
	VecF lastPos;
	Mouse& mouse;
	Camera& cam;
};