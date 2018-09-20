#pragma once
#include "Camera.h"
#include "Mouse.h"

class MouseCameraController
{
public:
	MouseCameraController(Camera& cam)
		:
		cam(cam)
	{}
	void ProcessCommand(bool isEngaged, const VecI& mousePos)
	{
		if (isEngaged)
		{
			lastPos = (VecF)mousePos;
		}
		engaged = isEngaged;
	}
	void Update(Mouse& mouse)
	{
		if (engaged)
		{

			const auto curPos = (VecF)mouse.GetPos();
			auto delta = curPos - lastPos;
			//delta.x = -delta.x; // fixes the disconnect between screen coords and math coords
			cam.MoveBy(delta);
			lastPos = curPos;
		}
	}
private:
	bool engaged = false;
	VecF lastPos;
	Camera& cam;
};